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

#ident "$XORP: xorp/libxipc/test_finder_events.cc,v 1.3 2003/06/01 21:37:28 hodson Exp $"

#include <list>
#include <vector>

#include "finder_module.h"

#include "libxorp/eventloop.hh"
#include "libxorp/status_codes.h"
#include "libxorp/xlog.h"

#include "finder_server.hh"
#include "finder_tcp_messenger.hh"
#include "finder_xrl_target.hh"
#include "permits.hh"
#include "sockutil.hh"

#include "xrl_std_router.hh"

#include "finder_event_notifier_xif.hh"
#include "test_finder_events_base.hh"

///////////////////////////////////////////////////////////////////////////////
//
// Constants
//

static const char *program_name         = "test_finder_events";
static const char *program_description  = "Test Finder events are "
					  "properly reported";
static const char *program_version_id   = "0.1";
static const char *program_date         = "May, 2003";
static const char *program_copyright    = "See file LICENSE.XORP";
static const char *program_return_value = "0 on success, 1 if test error, 2 if internal error";

///////////////////////////////////////////////////////////////////////////////
//
// Verbosity level control
//

static bool s_verbose = false;
bool verbose()                  { return s_verbose; }
void set_verbose(bool v)        { s_verbose = v; }

#define verbose_log(x...) _verbose_log(__FILE__,__LINE__, x)

#define _verbose_log(file, line, x...)					\
do {									\
    if (verbose()) {							\
	const char *wh = strrchr(file, '/');				\
	wh = (wh) ? wh + 1 : file;					\
	struct timeval t;						\
	gettimeofday(&t, 0);						\
 	printf("From %s:%d at %ld.%06ld: ", wh, line,			\
	       t.tv_sec, t.tv_usec);					\
	printf(x);							\
    }									\
} while(0)


/**
 * @short Test class that registers for event notifications with the finder.
 */
class FinderEventObserver
{
public:
    struct Watch {
	set<string> instance_names;
    };

    typedef map<string, Watch> Watches;

public:
    FinderEventObserver(EventLoop& e, IPv4 finder_addr, uint16_t finder_port)
	: _xrl_router(e, "finder_event_observer", finder_addr, finder_port)
    {
    }

    void finder_register_interest_cb(const XrlError& e,
				     string	     class_name)
    {
	XLOG_ASSERT(e == XrlError::OKAY());
	_watches[class_name];
    }

    void add_class_to_watch(const string& class_name)
    {
	XrlFinderEventNotifierV0p1Client cl(&_xrl_router);
	bool r = cl.send_register_class_event_interest(
			 "finder", _xrl_router.instance_name(), class_name,
		callback(this,
			 &FinderEventObserver::finder_register_interest_cb,
			 class_name));
	XLOG_ASSERT(r == true);
    }

    void finder_deregister_interest_cb(const XrlError& e,
				       string	       class_name)
    {
	XLOG_ASSERT(e == XrlError::OKAY());
	map<string,Watch>::iterator wi = _watches.find(class_name);
	XLOG_ASSERT(wi != _watches.end());
	_watches.erase(wi);
    }

    void remove_class_to_watch(const string& class_name)
    {
	XrlFinderEventNotifierV0p1Client cl(&_xrl_router);
	bool r = cl.send_deregister_class_event_interest(
			 "finder", _xrl_router.instance_name(), class_name,
		callback(this,
			 &FinderEventObserver::finder_deregister_interest_cb,
			 class_name));
	XLOG_ASSERT(r == true);
    }

    void birth_event(const string& class_name, const string& instance_name)
    {
	map<string,Watch>::iterator wi = _watches.find(class_name);
	XLOG_ASSERT(wi != _watches.end());
	Watch& w = wi->second;
	set<string>::iterator si = w.instance_names.find(instance_name);
	XLOG_ASSERT(si == w.instance_names.end());
	w.instance_names.insert(instance_name);
	verbose_log("Birth in class \"%s\", it's a \"%s\"\n",
		    class_name.c_str(), instance_name.c_str());
    }

    void death_event(const string& class_name, const string& instance_name)
    {
	map<string,Watch>::iterator wi = _watches.find(class_name);
	XLOG_ASSERT(wi != _watches.end());
	Watch& w = wi->second;
	set<string>::iterator si = w.instance_names.find(instance_name);
	XLOG_ASSERT(si != w.instance_names.end());
	w.instance_names.erase(si);
	verbose_log("Death in class \"%s\", it's a \"%s\"\n",
		    class_name.c_str(), instance_name.c_str());
    }

    uint32_t instance_count(const string& class_name)
    {
	map<string,Watch>::const_iterator wi = _watches.find(class_name);
	if (wi == _watches.end())
	    return 0;
	return wi->second.instance_names.size();
    }

    const Watches& watches() const { return _watches; }

    XrlRouter* router() { return &_xrl_router; }

protected:
    Watches	 _watches;
    XrlStdRouter _xrl_router;
};


/**
 * @short Xrl Handler interface for FinderEventObserver.
 */
class FinderEventObserverXrlTarget : public XrlTestFinderEventsTargetBase
{
public:
    FinderEventObserverXrlTarget(FinderEventObserver& feo)
	: XrlTestFinderEventsTargetBase(feo.router()), _feo(feo)
    {
    }

    XrlCmdError common_0_1_get_target_name(string& name)
    {
	name = _feo.router()->name();
	return XrlCmdError::OKAY();
    }

    XrlCmdError common_0_1_get_version(string& version)
    {
	version = "0.0";
	return XrlCmdError::OKAY();
    }

    XrlCmdError common_0_1_get_status(uint32_t& status_enum,
				      string&	status_txt)
    {
	status_enum = PROC_READY;
	status_txt = "Ready.";
	return XrlCmdError::OKAY();
    }

    XrlCmdError common_0_1_shutdown()
    {
	//We don't normally want to shutdown a process through this
	//particular Xrl target.
	return XrlCmdError::COMMAND_FAILED();
    }

    XrlCmdError finder_event_observer_0_1_xrl_target_birth(const string& cls,
							   const string& ins)
    {
	_feo.birth_event(cls, ins);
	return XrlCmdError::OKAY();
    }

    XrlCmdError finder_event_observer_0_1_xrl_target_death(const string& cls,
							   const string& ins)
    {
	_feo.death_event(cls, ins);
	return XrlCmdError::OKAY();
    }

private:
    FinderEventObserver& _feo;
};


/**
 * @short Class containing components for Finder event observation.
 */
class FinderEventObserverPackage
{
public:
    FinderEventObserverPackage(EventLoop& e, IPv4 addr, uint16_t port)
	: _feo(e, addr, port), _feoxt(_feo)
    {
	_feo.router()->finalize();
    }
    inline FinderEventObserver& observer()		{ return _feo; }
protected:
    FinderEventObserver 	 _feo;
    FinderEventObserverXrlTarget _feoxt;
};


///////////////////////////////////////////////////////////////////////////////
//
// Test Class (to be watched)
//

class AnXrlTarget
{
public:
    AnXrlTarget(EventLoop& e, const char* class_name,
		IPv4 finder_addr, uint16_t finder_port)
	: _router(e, class_name, finder_addr, finder_port)
    {
	_router.finalize();
    }
    inline const string& instance_name() const
    {
	return _router.instance_name();
    }
    inline const string& class_name() const
    {
	return _router.class_name();
    }
private:
    XrlStdRouter _router;
};


///////////////////////////////////////////////////////////////////////////////
//
// Timed command requests
//

static void
create_observer(EventLoop*		     e,
		FinderEventObserverPackage** pp,
		IPv4			     addr,
		uint16_t		     port)
{
    verbose_log("Creating observer.\n");
    *pp = new FinderEventObserverPackage(*e, addr, port);
    FinderEventObserverPackage* p = *pp;
    p->observer().router()->finalize();
}

static void
destroy_observer(FinderEventObserverPackage** pp)
{
    verbose_log("Destroying observer.\n");
    delete *pp;
    *pp = 0;
}

static void
assert_observer_ready(FinderEventObserverPackage** pp)
{
    verbose_log("Checking observer is ready.\n");
    FinderEventObserverPackage* p = *pp;
    XLOG_ASSERT(p != 0);
    XLOG_ASSERT((p)->observer().router());
    XLOG_ASSERT((p)->observer().router()->connected());
    XLOG_ASSERT((p)->observer().router()->ready());
}

static void
add_watch_to_observer(FinderEventObserverPackage** pp,
		      const char*		   class_name)
{
    verbose_log("Adding watch to observer\n");
    FinderEventObserverPackage* p = *pp;
    XLOG_ASSERT(p != 0);
    XLOG_ASSERT((p)->observer().router());
    XLOG_ASSERT((p)->observer().router()->connected());
    p->observer().add_class_to_watch(class_name);
}

static void
assert_observer_watching(FinderEventObserverPackage** pp,
			 const char*		      class_name)
{
    FinderEventObserverPackage* p = *pp;
    XLOG_ASSERT(p != 0);
    XLOG_ASSERT(p->observer().watches().find(class_name) !=
		p->observer().watches().end());
}

static void
remove_watch_from_observer(FinderEventObserverPackage** pp,
			   const char*			class_name)
{
    verbose_log("Removing watch from observer\n");
    FinderEventObserverPackage* p = *pp;
    XLOG_ASSERT(p != 0);
    XLOG_ASSERT((p)->observer().router());
    XLOG_ASSERT((p)->observer().router()->connected());
    p->observer().remove_class_to_watch(class_name);
}

static void
assert_observer_not_watching(FinderEventObserverPackage** pp,
			     const char*		  class_name)
{
    FinderEventObserverPackage* p = *pp;
    XLOG_ASSERT(p != 0);
    XLOG_ASSERT(p->observer().watches().find(class_name) ==
		p->observer().watches().end());
}

static void
assert_observer_class_instance_count(FinderEventObserverPackage** pp,
				     const char*		  class_name,
				     uint32_t			  cnt)
{
    FinderEventObserverPackage* p = *pp;
    XLOG_ASSERT(p != 0);
    uint32_t icnt = p->observer().instance_count(class_name);
    XLOG_ASSERT(icnt == cnt);
}

static void
create_xrl_target(EventLoop*		e,
		  IPv4			finder_addr,
		  uint16_t		finder_port,
		  const char*		class_name,
		  list<AnXrlTarget*>* store)
{
    AnXrlTarget* a = new AnXrlTarget(*e, class_name, finder_addr, finder_port);
    store->push_back(a);
    verbose_log("Creating Xrl target \"%s\" in class \"%s\"\n",
		a->instance_name().c_str(), a->class_name().c_str());
}

static void
remove_oldest_xrl_target(list<AnXrlTarget*>* store)
{
    XLOG_ASSERT(store != 0 && store->empty() == false);
    AnXrlTarget* a = store->front();
    store->pop_front();
    verbose_log("Kill Xrl target \"%s\" in class \"%s\"\n",
		a->instance_name().c_str(), a->class_name().c_str());
    delete a;
}

static void
remove_any_xrl_target(list<AnXrlTarget*>* store)
{
    uint32_t n = store->size();
    XLOG_ASSERT(n > 0);

    n = (uint32_t)random() % n;
    list<AnXrlTarget*>::iterator i = store->begin();
    while (n > 0) {
	i++;
	n--;
    }
    XLOG_ASSERT(i != store->end());

    AnXrlTarget* a = *i;
    store->erase(i);
    verbose_log("Kill Xrl target \"%s\" in class \"%s\"\n",
		a->instance_name().c_str(), a->class_name().c_str());
    delete a;
}

static void
assert_xrl_target_count(list<AnXrlTarget*>* store,
			uint32_t cnt)
{
    uint32_t n = store->size();
    XLOG_ASSERT(n == cnt);
}


///////////////////////////////////////////////////////////////////////////////
//
// test main
//

static int
test_main(IPv4 finder_addr, uint16_t finder_port, bool use_internal_finder)
{
    EventLoop e;

    FinderServer* fs = 0;
    if (use_internal_finder) {
	fs = new FinderServer(e, finder_port, finder_addr);
    } else {
	verbose_log("Using external Finder\n");
    }

    FinderEventObserverPackage* pfeo = 0;

    list<AnXrlTarget*> tgt_store;

    uint32_t t0 = 1000;

    static uint32_t tstep = 500;
    static const uint32_t burst_cnt = 50;

    vector<XorpTimer> timers;

#define SPACED_EVENT(cb_args...)					\
	timers.push_back(e.new_oneoff_after_ms(t0, callback(cb_args)));	\
    	t0 += tstep;

    //
    // Test 1
    //
    // Create observer, clean up observer
    //

    SPACED_EVENT(create_observer, &e, &pfeo, finder_addr, finder_port);

    SPACED_EVENT(assert_observer_ready, &pfeo);

    SPACED_EVENT(add_watch_to_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_watching, &pfeo, "class_a");

    SPACED_EVENT(remove_watch_from_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_not_watching, &pfeo, "class_a");

    SPACED_EVENT(destroy_observer, &pfeo);

    SPACED_EVENT(assert_xrl_target_count, &tgt_store, 0u);

    //
    // Test 2
    //
    // Start an observer, spawn an observable, clean up an
    // observables, spawn an observable, clean it up, repeat over,
    // over then clean up observer.
    //
    SPACED_EVENT(create_observer, &e, &pfeo, finder_addr, finder_port);

    SPACED_EVENT(assert_observer_ready, &pfeo);

    SPACED_EVENT(add_watch_to_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_watching,&pfeo, "class_a");

    for (uint32_t i = 0; i < burst_cnt; i++) {
	SPACED_EVENT(create_xrl_target, &e, finder_addr, finder_port,
		     "class_a", &tgt_store);

	SPACED_EVENT(assert_observer_class_instance_count,
		     &pfeo, "class_a", 1u);

	SPACED_EVENT(remove_oldest_xrl_target, &tgt_store);

	SPACED_EVENT(assert_observer_class_instance_count,
		     &pfeo, "class_a", 0u);
    }

    SPACED_EVENT(create_xrl_target, &e, finder_addr, finder_port,
			  "class_b", &tgt_store);

    SPACED_EVENT(assert_observer_class_instance_count, &pfeo, "class_b", 0u);

    SPACED_EVENT(remove_oldest_xrl_target, &tgt_store);

    SPACED_EVENT(remove_watch_from_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_not_watching, &pfeo, "class_a");

    SPACED_EVENT(destroy_observer, &pfeo);

    SPACED_EVENT(assert_xrl_target_count, &tgt_store, 0u);

    //
    // Test 3
    //
    // Start an observer, spawn a group of observables, clean up
    // group of observables, clean up observer.
    //
    SPACED_EVENT(create_observer, &e, &pfeo, finder_addr, finder_port);

    SPACED_EVENT(assert_observer_ready, &pfeo);

    SPACED_EVENT(add_watch_to_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_watching,&pfeo, "class_a");

    for (uint32_t i = 1; i <= burst_cnt; i++) {
	SPACED_EVENT(create_xrl_target, &e, finder_addr, finder_port,
		     "class_a", &tgt_store);

	SPACED_EVENT(assert_observer_class_instance_count, &pfeo,
		     "class_a", i);
    }

    for (uint32_t i = 1; i <= burst_cnt ; i++) {
	SPACED_EVENT(remove_any_xrl_target, &tgt_store);

	SPACED_EVENT(assert_observer_class_instance_count, &pfeo,
		     "class_a", burst_cnt - i);
    }
    SPACED_EVENT(assert_observer_class_instance_count, &pfeo, "class_a", 0u);

    SPACED_EVENT(remove_watch_from_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_not_watching, &pfeo, "class_a");

    SPACED_EVENT(destroy_observer, &pfeo);

    SPACED_EVENT(assert_xrl_target_count, &tgt_store, 0u);

    //
    // Test 4
    //
    // Spawn a group of observables, spawn an observer, spawn some
    // more observables, delete some, delete the observer, clean up
    // observables.
    //

    for (uint32_t i = 1; i <= burst_cnt; i++) {
	SPACED_EVENT(create_xrl_target, &e, finder_addr, finder_port,
		     "class_a", &tgt_store);
    }

    SPACED_EVENT(create_observer, &e, &pfeo, finder_addr, finder_port);

    SPACED_EVENT(assert_observer_ready, &pfeo);

    SPACED_EVENT(add_watch_to_observer, &pfeo, "class_a");

    SPACED_EVENT(assert_observer_watching,&pfeo, "class_a");

    SPACED_EVENT(assert_observer_class_instance_count, &pfeo,
		 "class_a", burst_cnt);

    SPACED_EVENT(add_watch_to_observer, &pfeo, "class_b");

    SPACED_EVENT(assert_observer_watching,&pfeo, "class_b");

    for (uint32_t i = 1; i <= burst_cnt; i++) {
	SPACED_EVENT(create_xrl_target, &e, finder_addr, finder_port,
		     "class_b", &tgt_store);
    }

    SPACED_EVENT(assert_observer_class_instance_count, &pfeo,
		 "class_b", burst_cnt);

    for (uint32_t i = 1; i <= burst_cnt; i++) {
	SPACED_EVENT(remove_any_xrl_target, &tgt_store);
    }

    SPACED_EVENT(destroy_observer, &pfeo);

    for (uint32_t i = 1; i <= burst_cnt ; i++) {
	SPACED_EVENT(remove_any_xrl_target, &tgt_store);
    }
    SPACED_EVENT(assert_xrl_target_count, &tgt_store, 0u);

    bool end_flag = false;
    XorpTimer the_end = e.set_flag_after_ms(t0, &end_flag);

    while (end_flag == false) {
	e.run();
    }
    if (fs) delete fs;
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
// Standard test program rubble.
//

/**
 * Print program info to output stream.
 *
 * @param stream the output stream the print the program info to.
 */
static void
print_program_info(FILE *stream)
{
    fprintf(stream, "Name:          %s\n", program_name);
    fprintf(stream, "Description:   %s\n", program_description);
    fprintf(stream, "Version:       %s\n", program_version_id);
    fprintf(stream, "Date:          %s\n", program_date);
    fprintf(stream, "Copyright:     %s\n", program_copyright);
    fprintf(stream, "Return:        %s\n", program_return_value);
}

/**
 * Print program usage information to the stderr.
 *
 * @param progname the name of the program.
 */
static void
usage(const char* progname)
{
    print_program_info(stderr);
    fprintf(stderr, "usage: %s [-F <host>[:port]] [-v] [-h]\n", progname);
    fprintf(stderr, "       -F          : specify arguments for an external Finder instance\n");
    fprintf(stderr, "       -h          : usage (this message)\n");
    fprintf(stderr, "       -v          : verbose output\n");
}


static bool
parse_finder_arg(const char* host_colon_port,
		 IPv4&	     finder_addr,
		 uint16_t&   finder_port)
{
    string finder_host;

    const char* p = strstr(host_colon_port, ":");

    if (p) {
	finder_host = string(host_colon_port, p);
	finder_port = atoi(p + 1);
	if (finder_port == 0) {
	    fprintf(stderr, "Invalid port \"%s\"\n", p + 1);
	    return false;
	}
    } else {
	finder_host = string(host_colon_port);
	finder_port = FINDER_DEFAULT_PORT;
    }

    try {
	finder_addr = IPv4(finder_host.c_str());
    } catch (const InvalidString& ) {
	// host string may need resolving
	in_addr ia;
	if (address_lookup(finder_host, ia) == false) {
	    fprintf(stderr, "Invalid host \"%s\"\n", finder_host.c_str());
	    return false;
	}
	finder_addr.copy_in(ia);
    }
    return true;
}


int
main(int argc, char * const argv[])
{
    int ret_value = 0;
    const char* const argv0 = argv[0];

    IPv4 finder_addr = FINDER_DEFAULT_HOST;
    uint16_t finder_port = 16600;	// over-ridden for external finder
    bool use_internal_finder = true;

    int ch;
    while ((ch = getopt(argc, argv, "F:hv")) != -1) {
        switch (ch) {
	case 'F':
	    if (parse_finder_arg(optarg, finder_addr, finder_port) == false) {
		usage(argv[0]);
		return 1;
	    }
	    use_internal_finder = false;
	    break;
        case 'v':
            set_verbose(true);
            break;
        case 'h':
        case '?':
        default:
            usage(argv[0]);
            if (ch == 'h')
                return 0;
            else
                return 1;
        }
    }
    argc -= optind;
    argv += optind;

    //
    // Initialize and start xlog
    //
    xlog_init(argv0, NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);         // Least verbose messages
    // XXX: verbosity of the error messages temporary increased
    xlog_level_set_verbose(XLOG_LEVEL_ERROR, XLOG_VERBOSE_HIGH);
    xlog_add_default_output();
    xlog_start();

    XorpUnexpectedHandler x(xorp_unexpected_handler);
    try {
	ret_value = test_main(finder_addr, finder_port, use_internal_finder);
    } catch (...) {
        // Internal error
        xorp_print_standard_exceptions();
        ret_value = 2;
    }

    //
    // Gracefully stop and exit xlog
    //
    xlog_stop();
    xlog_exit();

    return (ret_value);
}
