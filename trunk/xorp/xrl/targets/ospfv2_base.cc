/*
 * Copyright (c) 2001-2005 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 */

#ident "$XORP: xorp/xrl/targets/ospfv2_base.cc,v 1.4 2005/09/07 22:48:54 pavlin Exp $"


#include "ospfv2_base.hh"


XrlOspfv2TargetBase::XrlOspfv2TargetBase(XrlCmdMap* cmds)
    : _cmds(cmds)
{
    if (_cmds)
	add_handlers();
}

XrlOspfv2TargetBase::~XrlOspfv2TargetBase()
{
    if (_cmds)
	remove_handlers();
}

bool
XrlOspfv2TargetBase::set_command_map(XrlCmdMap* cmds)
{
    if (_cmds == 0 && cmds) {
        _cmds = cmds;
        add_handlers();
        return true;
    }
    if (_cmds && cmds == 0) {
	remove_handlers();
        _cmds = cmds;
        return true;
    }
    return false;
}

const XrlCmdError
XrlOspfv2TargetBase::handle_common_0_1_get_target_name(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/get_target_name");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string name;
    try {
	XrlCmdError e = common_0_1_get_target_name(
	    name);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_target_name", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("name", name);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_common_0_1_get_version(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/get_version");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string version;
    try {
	XrlCmdError e = common_0_1_get_version(
	    version);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_version", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("version", version);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_common_0_1_get_status(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/get_status");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    uint32_t status;
    string reason;
    try {
	XrlCmdError e = common_0_1_get_status(
	    status,
	    reason);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_status", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("status", status);
	pxa_outputs->add("reason", reason);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_common_0_1_shutdown(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/shutdown");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = common_0_1_shutdown();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/shutdown", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_raw_packet4_client_0_1_recv(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 9) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(9), XORP_UINT_CAST(xa_inputs.size()), "raw_packet4_client/0.1/recv");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = raw_packet4_client_0_1_recv(
	    xa_inputs.get_string("if_name"),
	    xa_inputs.get_string("vif_name"),
	    xa_inputs.get_ipv4("src_address"),
	    xa_inputs.get_ipv4("dst_address"),
	    xa_inputs.get_uint32("ip_protocol"),
	    xa_inputs.get_int32("ip_ttl"),
	    xa_inputs.get_int32("ip_tos"),
	    xa_inputs.get_bool("ip_router_alert"),
	    xa_inputs.get_binary("payload"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "raw_packet4_client/0.1/recv", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_router_id(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_router_id");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_router_id(
	    xa_inputs.get_ipv4("id"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_router_id", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_create_area_router(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(2), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/create_area_router");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_create_area_router(
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_string("type"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/create_area_router", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_destroy_area_router(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/destroy_area_router");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_destroy_area_router(
	    xa_inputs.get_ipv4("area"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/destroy_area_router", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_create_peer(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 7) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(7), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/create_peer");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_create_peer(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("addr"),
	    xa_inputs.get_uint32("prefix_len"),
	    xa_inputs.get_uint32("mtu"),
	    xa_inputs.get_string("type"),
	    xa_inputs.get_ipv4("area"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/create_peer", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_delete_peer(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(2), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/delete_peer");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_delete_peer(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/delete_peer", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_peer_state(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 3) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(3), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_peer_state");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_peer_state(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_bool("enable"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_peer_state", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_add_neighbour(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 5) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(5), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/add_neighbour");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_add_neighbour(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_ipv4("neighbour_address"),
	    xa_inputs.get_ipv4("neighbour_id"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/add_neighbour", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_remove_neighbour(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 5) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(5), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/remove_neighbour");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_remove_neighbour(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_ipv4("neighbour_address"),
	    xa_inputs.get_ipv4("neighbour_id"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/remove_neighbour", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_router_priority(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(4), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_router_priority");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_router_priority(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_uint32("priority"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_router_priority", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_hello_interval(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(4), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_hello_interval");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_hello_interval(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_uint32("interval"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_hello_interval", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_router_dead_interval(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(4), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_router_dead_interval");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_router_dead_interval(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_uint32("interval"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_router_dead_interval", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_interface_cost(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(4), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_interface_cost");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_interface_cost(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_uint32("cost"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_interface_cost", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlOspfv2TargetBase::handle_ospfv2_0_1_set_inftransdelay(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(4), XORP_UINT_CAST(xa_inputs.size()), "ospfv2/0.1/set_inftransdelay");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = ospfv2_0_1_set_inftransdelay(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("area"),
	    xa_inputs.get_uint32("delay"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "ospfv2/0.1/set_inftransdelay", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

void
XrlOspfv2TargetBase::add_handlers()
{
	if (_cmds->add_handler("common/0.1/get_target_name",
	    callback(this, &XrlOspfv2TargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version",
	    callback(this, &XrlOspfv2TargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status",
	    callback(this, &XrlOspfv2TargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown",
	    callback(this, &XrlOspfv2TargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "common/0.1/shutdown");
	}
	if (_cmds->add_handler("raw_packet4_client/0.1/recv",
	    callback(this, &XrlOspfv2TargetBase::handle_raw_packet4_client_0_1_recv)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "raw_packet4_client/0.1/recv");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_router_id",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_router_id)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_router_id");
	}
	if (_cmds->add_handler("ospfv2/0.1/create_area_router",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_create_area_router)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/create_area_router");
	}
	if (_cmds->add_handler("ospfv2/0.1/destroy_area_router",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_destroy_area_router)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/destroy_area_router");
	}
	if (_cmds->add_handler("ospfv2/0.1/create_peer",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_create_peer)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/create_peer");
	}
	if (_cmds->add_handler("ospfv2/0.1/delete_peer",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_delete_peer)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/delete_peer");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_peer_state",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_peer_state)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_peer_state");
	}
	if (_cmds->add_handler("ospfv2/0.1/add_neighbour",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_add_neighbour)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/add_neighbour");
	}
	if (_cmds->add_handler("ospfv2/0.1/remove_neighbour",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_remove_neighbour)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/remove_neighbour");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_router_priority",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_router_priority)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_router_priority");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_hello_interval",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_hello_interval)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_hello_interval");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_router_dead_interval",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_router_dead_interval)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_router_dead_interval");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_interface_cost",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_interface_cost)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_interface_cost");
	}
	if (_cmds->add_handler("ospfv2/0.1/set_inftransdelay",
	    callback(this, &XrlOspfv2TargetBase::handle_ospfv2_0_1_set_inftransdelay)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "ospfv2", "ospfv2/0.1/set_inftransdelay");
	}
	_cmds->finalize();
}

void
XrlOspfv2TargetBase::remove_handlers()
{
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("raw_packet4_client/0.1/recv");
	_cmds->remove_handler("ospfv2/0.1/set_router_id");
	_cmds->remove_handler("ospfv2/0.1/create_area_router");
	_cmds->remove_handler("ospfv2/0.1/destroy_area_router");
	_cmds->remove_handler("ospfv2/0.1/create_peer");
	_cmds->remove_handler("ospfv2/0.1/delete_peer");
	_cmds->remove_handler("ospfv2/0.1/set_peer_state");
	_cmds->remove_handler("ospfv2/0.1/add_neighbour");
	_cmds->remove_handler("ospfv2/0.1/remove_neighbour");
	_cmds->remove_handler("ospfv2/0.1/set_router_priority");
	_cmds->remove_handler("ospfv2/0.1/set_hello_interval");
	_cmds->remove_handler("ospfv2/0.1/set_router_dead_interval");
	_cmds->remove_handler("ospfv2/0.1/set_interface_cost");
	_cmds->remove_handler("ospfv2/0.1/set_inftransdelay");
}
