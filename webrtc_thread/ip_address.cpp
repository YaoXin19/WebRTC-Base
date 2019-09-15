//
// Created by haha on 2019/9/15.
//

#include "ip_address.h"
#include "net_helpers.h"

bool IPFromString(const std::string& str, IPAddress* out) {
    if (!out)
        return false;
    in_addr addr;
    if (rtc::inet_pton(AF_INET, str.c_str(), &addr) == 0) { // ipv4
        return false; // ipv6
    } else {
        *out = IPAddress(addr);
    }
    return true;
}

in_addr IPAddress::ipv4_address() const {
    return u_.ip4;
}
