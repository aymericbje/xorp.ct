// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2007 International Computer Science Institute
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

// $XORP: xorp/fea/data_plane/fibconfig/fibconfig_forwarding_proc_linux.hh,v 1.1 2007/07/17 22:53:55 pavlin Exp $

#ifndef __FEA_DATA_PLANE_FIBCONFIG_FIBCONFIG_FORWARDING_PROC_LINUX_HH__
#define __FEA_DATA_PLANE_FIBCONFIG_FIBCONFIG_FORWARDING_PROC_LINUX_HH__

#include "fea/fibconfig_forwarding.hh"


class FibConfigForwardingProcLinux : public FibConfigForwarding {
public:
    /**
     * Constructor.
     *
     * @param fea_data_plane_manager the corresponding data plane manager
     * (@see FeaDataPlaneManager).
     */
    FibConfigForwardingProcLinux(FeaDataPlaneManager& fea_data_plane_manager);

    /**
     * Virtual destructor.
     */
    virtual ~FibConfigForwardingProcLinux();

    /**
     * Test whether the IPv4 unicast forwarding engine is enabled or disabled
     * to forward packets.
     * 
     * @param ret_value if true on return, then the IPv4 unicast forwarding
     * is enabled, otherwise is disabled.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int unicast_forwarding_enabled4(bool& ret_value, string& error_msg) const;

    /**
     * Test whether the IPv6 unicast forwarding engine is enabled or disabled
     * to forward packets.
     * 
     * @param ret_value if true on return, then the IPv6 unicast forwarding
     * is enabled, otherwise is disabled.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int unicast_forwarding_enabled6(bool& ret_value, string& error_msg) const;

    /**
     * Test whether the acceptance of IPv6 Router Advertisement messages is
     * enabled or disabled.
     * 
     * @param ret_value if true on return, then the acceptance of IPv6 Router
     * Advertisement messages is enabled, otherwise is disabled.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int accept_rtadv_enabled6(bool& ret_value, string& error_msg) const;

    /**
     * Set the IPv4 unicast forwarding engine to enable or disable forwarding
     * of packets.
     * 
     * @param v if true, then enable IPv4 unicast forwarding, otherwise
     * disable it.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int set_unicast_forwarding_enabled4(bool v, string& error_msg);

    /**
     * Set the IPv6 unicast forwarding engine to enable or disable forwarding
     * of packets.
     * 
     * @param v if true, then enable IPv6 unicast forwarding, otherwise
     * disable it.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int set_unicast_forwarding_enabled6(bool v, string& error_msg);

    /**
     * Enable or disable the acceptance of IPv6 Router Advertisement messages
     * from other routers. It should be enabled for hosts, and disabled for
     * routers.
     * 
     * @param v if true, then enable the acceptance of IPv6 Router
     * Advertisement messages, otherwise disable it.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int set_accept_rtadv_enabled6(bool v, string& error_msg);

private:
    static const string PROC_LINUX_FORWARDING_FILE_V4;
    static const string PROC_LINUX_FORWARDING_FILE_V6;
};

#endif // __FEA_DATA_PLANE_FIBCONFIG_FIBCONFIG_FORWARDING_PROC_LINUX_HH__
