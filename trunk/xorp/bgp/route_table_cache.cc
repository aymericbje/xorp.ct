// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2003 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/bgp/route_table_cache.cc,v 1.18 2004/02/25 15:20:20 atanu Exp $"

// #define DEBUG_LOGGING
#define DEBUG_PRINT_FUNCTION_NAME

#include "bgp_module.h"
#include "libxorp/xlog.h"
#include "route_table_cache.hh"
#include <map>

template<class A>
CacheTable<A>::CacheTable(string table_name,  
			  Safi safi,
			  BGPRouteTable<A> *parent_table)
    : BGPRouteTable<A>("CacheTable-" + table_name, safi)
{
    _parent = parent_table;
}

template<class A>
void
CacheTable<A>::flush_cache()
{
    debug_msg("%s\n", tablename().c_str());
    _route_table.delete_all_nodes();
}

template<class A>
int
CacheTable<A>::add_route(const InternalMessage<A> &rtmsg,
			 BGPRouteTable<A> *caller)
{
    debug_msg("\n         %s\n caller: %s\n rtmsg: %p route: %p\n%s\n",
	      tablename().c_str(),
	      caller ? caller->tablename().c_str() : "NULL",
	      &rtmsg,
	      rtmsg.route(),
	      rtmsg.str().c_str());

    XLOG_ASSERT(caller == _parent);
    XLOG_ASSERT(_next_table != NULL);

    //a cache table is never going to be the last table
    IPNet<A> net = rtmsg.net();

    //check we don't already have this cached
    assert(_route_table.lookup_node(net) == _route_table.end());

    if (rtmsg.changed()==false) {
	return _next_table->add_route(rtmsg, (BGPRouteTable<A>*)this);
    } else {
	//The route was changed.  

	//It's the responsibility of the recipient of a changed route
	//to store it or free it.  We're the final recipient, so we
	//can rely on rtmsg.route() not to go away.
	const SubnetRoute<A> *msg_route = rtmsg.route();
	//store it locally
	typename RefTrie<A, const SubnetRoute<A> >::iterator ti;
	ti = _route_table.insert(msg_route->net(), *msg_route);
	debug_msg("Caching route: %p net: %s atts: %p  %s\n", msg_route,
	       msg_route->net().str().c_str(), 
	       (msg_route->attributes()), 
	       msg_route->str().c_str());

	//progogate downstream
	InternalMessage<A> new_rt_msg(&(ti.payload()), rtmsg.origin_peer(),
				      rtmsg.genid());
	if (rtmsg.push()) new_rt_msg.set_push();
	int result = _next_table->add_route(new_rt_msg, 
					    (BGPRouteTable<A>*)this);

	rtmsg.inactivate();

	switch (result) {
	case ADD_USED:
	    ti.payload().set_in_use(true);
#ifdef DUMP_FROM_CACHE
	    //Our cached copy was used, but we need to tell upstream
	    //that their unmodified version was unused.
	    return ADD_UNUSED;
#else
	    //XXX see comment in dump_entire_table - disable dumping
	    //from the cache, so we need to return ADD_USED for now.
	    return ADD_USED;
#endif
	case ADD_UNUSED:
	    ti.payload().set_in_use(false);
	    return ADD_UNUSED;
	default:
	    //In the case of a failure, we don't know what to believe.
	    //To be safe we set in_use to true, although it may reduce
	    //efficiency.
	    msg_route->set_in_use(true);
	    return result;
	}
    }
}

template<class A>
int
CacheTable<A>::replace_route(const InternalMessage<A> &old_rtmsg, 
			     const InternalMessage<A> &new_rtmsg, 
			     BGPRouteTable<A> *caller)
{
    debug_msg("\n         %s\n"
	      "caller: %s\n"
	      "old rtmsg: %p new rtmsg: %p "
	      "old route: %p"
	      "new route: %p"
	      "old: %s\n new: %s\n",
	      tablename().c_str(),
	      caller ? caller->tablename().c_str() : "NULL",
	      &old_rtmsg,
	      &new_rtmsg,
	      old_rtmsg.route(),
	      new_rtmsg.route(),
	      old_rtmsg.str().c_str(),
	      new_rtmsg.str().c_str());

    XLOG_ASSERT(caller == _parent);
    XLOG_ASSERT(_next_table != NULL);

    IPNet<A> net = old_rtmsg.net();
    XLOG_ASSERT(net == new_rtmsg.net());

    SubnetRouteConstRef<A> *old_route_reference = NULL;
    const InternalMessage<A> *old_rtmsg_ptr = &old_rtmsg;
    int result = ADD_USED;

    //do we have the old route cached?
    if (old_rtmsg.changed()==true) {
	typename RefTrie<A, const SubnetRoute<A> >::iterator iter;
	iter = _route_table.lookup_node(net);
	if (iter == _route_table.end()) {
	    //We don't flush the cache, so this should not happen
	    XLOG_UNREACHABLE();
	} else {
	    // Preserve the route.  Taking a reference will prevent
	    // the route being immediately deleted when it's erased
	    // from the RefTrie.  Deletion will occur later when the
	    // reference is deleted.
	    const SubnetRoute<A> *old_route = &(iter.payload());
	    old_route_reference = new SubnetRouteConstRef<A>(old_route);

	    old_rtmsg_ptr = new InternalMessage<A>(old_route,
						   old_rtmsg.origin_peer(),
						   old_rtmsg.genid());

	    //delete it from our cache, 
	    _route_table.erase(old_rtmsg.net());

	    //It's the responsibility of the recipient of a changed
	    //route to store it or free it.
	    //Free the route from the message.
	    old_rtmsg.inactivate();
	}
    }

    //do we need to cache the new route?
    if (new_rtmsg.changed()==false) {
	result = _next_table->replace_route(*old_rtmsg_ptr, 
					    new_rtmsg, 
					    (BGPRouteTable<A>*)this);
    } else {
	//Route was changed.

	//It's the responsibility of the recipient of a changed route
	//to store it or free it.  We're the final recipient, so we
	//can rely on rtmsg.route() not to go away.
	const SubnetRoute<A> *new_route = new_rtmsg.route();
	//store it locally
	typename RefTrie<A, const SubnetRoute<A> >::iterator ti;
	ti = _route_table.insert(net, *new_route);

	//progogate downstream
	InternalMessage<A> new_rtmsg_copy(&(ti.payload()),
					  new_rtmsg.origin_peer(),
					  new_rtmsg.genid());
	if (new_rtmsg.push()) new_rtmsg_copy.set_push();
	result = _next_table->replace_route(*old_rtmsg_ptr,
					    new_rtmsg_copy, 
					    (BGPRouteTable<A>*)this);
	new_rtmsg.inactivate();

	switch (result) {
	case ADD_USED:
	    ti.payload().set_in_use(true);
	    break;
	case ADD_UNUSED:
	    ti.payload().set_in_use(false);
	    break;
	default:
	    //In the case of a failure, we don't know what to believe.
	    //To be safe we set in_use to true, although it may reduce
	    //efficiency.
	    ti.payload().set_in_use(true);
	}
    }

    if (old_rtmsg_ptr != &old_rtmsg) {
	delete old_rtmsg_ptr;
	assert(old_route_reference != NULL);
	delete old_route_reference;
    }

    return result;
}

template<class A>
int
CacheTable<A>::delete_route(const InternalMessage<A> &rtmsg, 
			    BGPRouteTable<A> *caller)
{

    debug_msg("\n         %s\n caller: %s\n rtmsg: %p route: %p\n%s\n",
	      tablename().c_str(),
	      caller ? caller->tablename().c_str() : "NULL",
	      &rtmsg,
	      rtmsg.route(),
	      rtmsg.str().c_str());

    XLOG_ASSERT(caller == _parent);
    XLOG_ASSERT(_next_table != NULL);
    IPNet<A> net = rtmsg.net();

    //do we already have this cached?
    typename RefTrie<A, const SubnetRoute<A> >::iterator iter;
    iter = _route_table.lookup_node(net);
    if (iter != _route_table.end()) {
	const SubnetRoute<A> *existing_route = &(iter.payload());
	debug_msg("Found cached route: %s\n", existing_route->str().c_str());

	// Preserve the route.  Taking a reference will prevent the
	// route being deleted when it's erased from the RefTrie.
	// Deletion will occur when the reference goes out of scope.
	SubnetRouteConstRef<A> route_reference(existing_route);

	//delete it from our cache trie 
	_route_table.erase(net);

	InternalMessage<A> old_rt_msg(existing_route,
				      rtmsg.origin_peer(),
				      rtmsg.genid());
	if (rtmsg.push()) old_rt_msg.set_push();

	int result = 0;
	result = _next_table->delete_route(old_rt_msg, 
					   (BGPRouteTable<A>*)this);

	if (rtmsg.changed()) {
	    //It's the responsibility of the recipient of a changed
	    //route to store it or free it.
	    //Free the route from the message.
	    rtmsg.inactivate();
	}
	return result;
    }

    //we don't flush the cache, so this should simply never happen.
    XLOG_ASSERT(!rtmsg.changed());

    //If we get here, route was not cached and was not modified.
    return _next_table->delete_route(rtmsg, (BGPRouteTable<A>*)this);
}

template<class A>
int
CacheTable<A>::push(BGPRouteTable<A> *caller) {
    assert(caller == _parent);
    return _next_table->push((BGPRouteTable<A>*)this);
}

template<class A>
int 
CacheTable<A>::route_dump(const InternalMessage<A> &rtmsg,
			  BGPRouteTable<A> *caller,
			  const PeerHandler *dump_peer) {
    assert(caller == _parent);
    if (rtmsg.changed()) {
	//Check we've got it cached.  Clear the changed bit so we
	//don't confuse anyone downstream.
	IPNet<A> net = rtmsg.route()->net();
	typename RefTrie<A, const SubnetRoute<A> >::iterator iter;
	iter = _route_table.lookup_node(net);
	assert(iter != _route_table.end());

	//It's the responsibility of the recipient of a changed route
	//to store or delete it.  We don't need it anymore (we found
	//the cached copy) so we delete it.
	rtmsg.route()->unref();

	//the message we pass on needs to contain our cached
	//route, because the MED info in it may not be in the original
	//version of the route.
	InternalMessage<A> new_msg(&(iter.payload()), rtmsg.origin_peer(),
				   rtmsg.genid());
	return _next_table->route_dump(new_msg, (BGPRouteTable<A>*)this, 
				       dump_peer);
    } else {
	return _next_table->route_dump(rtmsg, (BGPRouteTable<A>*)this, 
				       dump_peer);
    }
}

template<class A>
const SubnetRoute<A>*
CacheTable<A>::lookup_route(const IPNet<A> &net) const {
    //return our cached copy if there is one, otherwise ask our parent
    typename RefTrie<A, const SubnetRoute<A> >::iterator iter;
    iter = _route_table.lookup_node(net);
    if (iter != _route_table.end())
	return &(iter.payload());
    else
	return _parent->lookup_route(net);
}

template<class A>
void
CacheTable<A>::route_used(const SubnetRoute<A>* rt, bool in_use){
    _parent->route_used(rt, in_use);
}

template<class A>
string
CacheTable<A>::str() const {
    string s = "CacheTable<A>" + tablename();
    return s;
}

/* mechanisms to implement flow control in the output plumbing */
template<class A>
void 
CacheTable<A>::output_state(bool busy, BGPRouteTable<A> *next_table) {
    XLOG_ASSERT(_next_table == next_table);

    _parent->output_state(busy, this);
}

template<class A>
bool 
CacheTable<A>::get_next_message(BGPRouteTable<A> *next_table) {
    XLOG_ASSERT(_next_table == next_table);

    return _parent->get_next_message(this);
}

template class CacheTable<IPv4>;
template class CacheTable<IPv6>;





