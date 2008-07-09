/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 */

#ident "$XORP: xorp/xrl/targets/cli_base.cc,v 1.22 2007/07/12 21:46:11 pavlin Exp $"


#include "cli_base.hh"


XrlCliTargetBase::XrlCliTargetBase(XrlCmdMap* cmds)
    : _cmds(cmds)
{
    if (_cmds)
	add_handlers();
}

XrlCliTargetBase::~XrlCliTargetBase()
{
    if (_cmds)
	remove_handlers();
}

bool
XrlCliTargetBase::set_command_map(XrlCmdMap* cmds)
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
XrlCliTargetBase::handle_common_0_1_get_target_name(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
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
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
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
XrlCliTargetBase::handle_common_0_1_get_version(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
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
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
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
XrlCliTargetBase::handle_common_0_1_get_status(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
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
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
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
XrlCliTargetBase::handle_common_0_1_shutdown(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
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
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_enable_cli(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/enable_cli");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_enable_cli(
	    xa_inputs.get_bool("enable"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/enable_cli", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_start_cli(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/start_cli");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_start_cli();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/start_cli", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_stop_cli(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/stop_cli");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_stop_cli();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/stop_cli", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_add_enable_cli_access_from_subnet4(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/add_enable_cli_access_from_subnet4");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_add_enable_cli_access_from_subnet4(
	    xa_inputs.get_ipv4net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/add_enable_cli_access_from_subnet4", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_add_enable_cli_access_from_subnet6(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/add_enable_cli_access_from_subnet6");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_add_enable_cli_access_from_subnet6(
	    xa_inputs.get_ipv6net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/add_enable_cli_access_from_subnet6", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_delete_enable_cli_access_from_subnet4(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/delete_enable_cli_access_from_subnet4");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_delete_enable_cli_access_from_subnet4(
	    xa_inputs.get_ipv4net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/delete_enable_cli_access_from_subnet4", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_delete_enable_cli_access_from_subnet6(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/delete_enable_cli_access_from_subnet6");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_delete_enable_cli_access_from_subnet6(
	    xa_inputs.get_ipv6net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/delete_enable_cli_access_from_subnet6", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_add_disable_cli_access_from_subnet4(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/add_disable_cli_access_from_subnet4");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_add_disable_cli_access_from_subnet4(
	    xa_inputs.get_ipv4net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/add_disable_cli_access_from_subnet4", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_add_disable_cli_access_from_subnet6(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/add_disable_cli_access_from_subnet6");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_add_disable_cli_access_from_subnet6(
	    xa_inputs.get_ipv6net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/add_disable_cli_access_from_subnet6", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_delete_disable_cli_access_from_subnet4(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/delete_disable_cli_access_from_subnet4");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_delete_disable_cli_access_from_subnet4(
	    xa_inputs.get_ipv4net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/delete_disable_cli_access_from_subnet4", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_delete_disable_cli_access_from_subnet6(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/delete_disable_cli_access_from_subnet6");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_delete_disable_cli_access_from_subnet6(
	    xa_inputs.get_ipv6net("subnet_addr"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/delete_disable_cli_access_from_subnet6", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_add_cli_command(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 6) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(6), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/add_cli_command");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_add_cli_command(
	    xa_inputs.get_string("processor_name"),
	    xa_inputs.get_string("command_name"),
	    xa_inputs.get_string("command_help"),
	    xa_inputs.get_bool("is_command_cd"),
	    xa_inputs.get_string("command_cd_prompt"),
	    xa_inputs.get_bool("is_command_processor"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/add_cli_command", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlCliTargetBase::handle_cli_manager_0_1_delete_cli_command(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(2), XORP_UINT_CAST(xa_inputs.size()), "cli_manager/0.1/delete_cli_command");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = cli_manager_0_1_delete_cli_command(
	    xa_inputs.get_string("processor_name"),
	    xa_inputs.get_string("command_name"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "cli_manager/0.1/delete_cli_command", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

void
XrlCliTargetBase::add_handlers()
{
	if (_cmds->add_handler("common/0.1/get_target_name",
	    callback(this, &XrlCliTargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version",
	    callback(this, &XrlCliTargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status",
	    callback(this, &XrlCliTargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown",
	    callback(this, &XrlCliTargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "common/0.1/shutdown");
	}
	if (_cmds->add_handler("cli_manager/0.1/enable_cli",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_enable_cli)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/enable_cli");
	}
	if (_cmds->add_handler("cli_manager/0.1/start_cli",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_start_cli)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/start_cli");
	}
	if (_cmds->add_handler("cli_manager/0.1/stop_cli",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_stop_cli)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/stop_cli");
	}
	if (_cmds->add_handler("cli_manager/0.1/add_enable_cli_access_from_subnet4",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_add_enable_cli_access_from_subnet4)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/add_enable_cli_access_from_subnet4");
	}
	if (_cmds->add_handler("cli_manager/0.1/add_enable_cli_access_from_subnet6",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_add_enable_cli_access_from_subnet6)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/add_enable_cli_access_from_subnet6");
	}
	if (_cmds->add_handler("cli_manager/0.1/delete_enable_cli_access_from_subnet4",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_delete_enable_cli_access_from_subnet4)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/delete_enable_cli_access_from_subnet4");
	}
	if (_cmds->add_handler("cli_manager/0.1/delete_enable_cli_access_from_subnet6",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_delete_enable_cli_access_from_subnet6)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/delete_enable_cli_access_from_subnet6");
	}
	if (_cmds->add_handler("cli_manager/0.1/add_disable_cli_access_from_subnet4",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_add_disable_cli_access_from_subnet4)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/add_disable_cli_access_from_subnet4");
	}
	if (_cmds->add_handler("cli_manager/0.1/add_disable_cli_access_from_subnet6",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_add_disable_cli_access_from_subnet6)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/add_disable_cli_access_from_subnet6");
	}
	if (_cmds->add_handler("cli_manager/0.1/delete_disable_cli_access_from_subnet4",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_delete_disable_cli_access_from_subnet4)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/delete_disable_cli_access_from_subnet4");
	}
	if (_cmds->add_handler("cli_manager/0.1/delete_disable_cli_access_from_subnet6",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_delete_disable_cli_access_from_subnet6)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/delete_disable_cli_access_from_subnet6");
	}
	if (_cmds->add_handler("cli_manager/0.1/add_cli_command",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_add_cli_command)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/add_cli_command");
	}
	if (_cmds->add_handler("cli_manager/0.1/delete_cli_command",
	    callback(this, &XrlCliTargetBase::handle_cli_manager_0_1_delete_cli_command)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "cli", "cli_manager/0.1/delete_cli_command");
	}
	_cmds->finalize();
}

void
XrlCliTargetBase::remove_handlers()
{
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("cli_manager/0.1/enable_cli");
	_cmds->remove_handler("cli_manager/0.1/start_cli");
	_cmds->remove_handler("cli_manager/0.1/stop_cli");
	_cmds->remove_handler("cli_manager/0.1/add_enable_cli_access_from_subnet4");
	_cmds->remove_handler("cli_manager/0.1/add_enable_cli_access_from_subnet6");
	_cmds->remove_handler("cli_manager/0.1/delete_enable_cli_access_from_subnet4");
	_cmds->remove_handler("cli_manager/0.1/delete_enable_cli_access_from_subnet6");
	_cmds->remove_handler("cli_manager/0.1/add_disable_cli_access_from_subnet4");
	_cmds->remove_handler("cli_manager/0.1/add_disable_cli_access_from_subnet6");
	_cmds->remove_handler("cli_manager/0.1/delete_disable_cli_access_from_subnet4");
	_cmds->remove_handler("cli_manager/0.1/delete_disable_cli_access_from_subnet6");
	_cmds->remove_handler("cli_manager/0.1/add_cli_command");
	_cmds->remove_handler("cli_manager/0.1/delete_cli_command");
}
