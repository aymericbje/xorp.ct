// vim:set sts=4 ts=8:

// Copyright (c) 2001-2005 International Computer Science Institute
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

#ident "$XORP: xorp/policy/policy_target.cc,v 1.3 2005/07/01 22:54:34 abittau Exp $"

#include "policy_module.h"
#include "config.h"

#include "policy_target.hh"
#include "policy/common/policy_utils.hh"


// static members
string PolicyTarget::policy_target_name = "policy";



PolicyTarget::PolicyTarget(XrlStdRouter& rtr) :
    _running(true), _commit_delay(2000), 
    _process_watch(rtr),
    _conf(_process_watch),
    _filter_manager(_conf.import_filters(),
		    _conf.sourcematch_filters(),
		    _conf.export_filters(),
		    _conf.sets(),
		    _conf.tagmap(),
		    rtr,
		    _process_watch)

{
    _conf.set_filter_manager(_filter_manager);
    _process_watch.set_notifier(_filter_manager);
}

bool
PolicyTarget::running()
{
    return _running;
}

void
PolicyTarget::shutdown()
{
    _running = false;
}


void
PolicyTarget::create_term(const string& policy, const uint64_t& order,
			  const string& term)
{
    _conf.create_term(policy, order, term);
}

void
PolicyTarget::delete_term(const string& policy, const string& term)
{
    _conf.delete_term(policy,term);
}

void
PolicyTarget::update_term_block(const string& policy,
				const string& term,
				const uint32_t& block,
				const uint64_t& order,
				const string& variable,
				const string& op,
				const string& arg)
{
    _conf.update_term_block(policy, term, block, order, variable, op, arg);
}

void
PolicyTarget::create_policy(const string& policy)
{
    _conf.create_policy(policy);
}

void
PolicyTarget::delete_policy(const string& policy)
{
    _conf.delete_policy(policy);
}

void
PolicyTarget::create_set(const string& name)
{
    _conf.create_set(name);
}

void
PolicyTarget::update_set(const string& name, const string& element)
{
    _conf.update_set(name,element);
}

void
PolicyTarget::delete_set(const string& name)
{
    _conf.delete_set(name);
}

void
PolicyTarget::update_import(const string& protocol,
			    const string& policies)
{
    // convert the policies to a list
    list<string> pols;
    policy_utils::str_to_list(policies,pols);

    _conf.update_imports(protocol,pols);

    // commit after a bit, as we may get conf changes... especially on "global
    // conf change" or at startup
    _conf.commit(_commit_delay);
}

void
PolicyTarget::update_export(const string& protocol,
			    const string& policies)
{
    // convert policies to a list
    list<string> pols;
    policy_utils::str_to_list(policies,pols);

    _conf.update_exports(protocol,pols);

    // try to aggregate commits by delaying them
    _conf.commit(_commit_delay);
}

void
PolicyTarget::add_varmap(const string& protocol, const string& variable,
			 const string& type, const string& access)
{
    _conf.add_varmap(protocol, variable, type, access);
}

void
PolicyTarget::commit(uint32_t msec)
{
    _conf.commit(msec);
}

string
PolicyTarget::dump_state(uint32_t id)
{
    return _conf.dump_state(id);
}

void
PolicyTarget::birth(const string& tclass, const string& /* tinstance */)
{
    _process_watch.birth(tclass);
}

void
PolicyTarget::death(const string& tclass, const string& /* tinstance */)
{
    _process_watch.death(tclass);
}
