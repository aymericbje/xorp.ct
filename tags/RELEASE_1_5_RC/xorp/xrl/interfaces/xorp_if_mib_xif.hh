/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/xorp_if_mib_xif.hh,v 1.11 2007/07/12 21:37:32 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_XORP_IF_MIB_XIF_HH__
#define __XRL_INTERFACES_XORP_IF_MIB_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifXorpIfMib"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlXorpIfMibV0p1Client {
public:
    XrlXorpIfMibV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlXorpIfMibV0p1Client() {}

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr LoadMibCB;
    /**
     *  Send Xrl intended to:
     *
     *  Load a MIB module
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param mod_name the mib module file name (without extension)
     *
     *  @param abs_path absolute path to the module file
     */
    bool send_load_mib(
	const char*	dst_xrl_target_name,
	const string&	mod_name,
	const string&	abs_path,
	const LoadMibCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr UnloadMibCB;
    /**
     *  Send Xrl intended to:
     *
     *  Unload a MIB module
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     */
    bool send_unload_mib(
	const char*	dst_xrl_target_name,
	const uint32_t&	mib_index,
	const UnloadMibCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_load_mib(
	const XrlError&	e,
	XrlArgs*	a,
	LoadMibCB		cb
    );

    void unmarshall_unload_mib(
	const XrlError&	e,
	XrlArgs*	a,
	UnloadMibCB		cb
    );

};

#endif /* __XRL_INTERFACES_XORP_IF_MIB_XIF_HH__ */
