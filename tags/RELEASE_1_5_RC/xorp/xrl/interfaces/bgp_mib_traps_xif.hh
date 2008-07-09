/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/bgp_mib_traps_xif.hh,v 1.12 2007/07/12 21:37:27 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_BGP_MIB_TRAPS_XIF_HH__
#define __XRL_INTERFACES_BGP_MIB_TRAPS_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifBgpMibTraps"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlBgpMibTrapsV0p1Client {
public:
    XrlBgpMibTrapsV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlBgpMibTrapsV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr SendBgpEstablishedTrapCB;
    /**
     *  Send Xrl intended to:
     *
     *  Send bgpEstablished trap
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     */
    bool send_send_bgp_established_trap(
	const char*	dst_xrl_target_name,
	const string&	bgp_last_error,
	const uint32_t&	bgp_state,
	const SendBgpEstablishedTrapCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SendBgpBackwardTransitionTrapCB;
    /**
     *  Send Xrl intended to:
     *
     *  Send bgpBackwardTransition trap
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     */
    bool send_send_bgp_backward_transition_trap(
	const char*	dst_xrl_target_name,
	const string&	bgp_last_error,
	const uint32_t&	bgp_state,
	const SendBgpBackwardTransitionTrapCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_send_bgp_established_trap(
	const XrlError&	e,
	XrlArgs*	a,
	SendBgpEstablishedTrapCB		cb
    );

    void unmarshall_send_bgp_backward_transition_trap(
	const XrlError&	e,
	XrlArgs*	a,
	SendBgpBackwardTransitionTrapCB		cb
    );

};

#endif /* __XRL_INTERFACES_BGP_MIB_TRAPS_XIF_HH__ */
