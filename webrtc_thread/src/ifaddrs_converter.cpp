//
// Created by haha on 9/23/19.
//

#include "ifaddrs_converter.h"

#include <net/if.h>
#include <netinet/in.h>
#include <ifaddrs.h>

bool IfAddrsConverter::ConvertIfAddrsToIPAddress(const struct ifaddrs* interface, InterfaceAddress* ip, IPAddress* mask) {
    switch(interface->ifa_addr->sa_family) {
        case AF_INET: {
            *ip = InterfaceAddress(IPAddress(reinterpret_cast<sockaddr_in*>(interface->ifa_addr)->sin_addr));
            *mask = IPAddress(reinterpret_cast<sockaddr_in*>(interface->ifa_netmask)->sin_addr);
            return true;
        }
        case AF_INET6: {
            return false;
        }
        default: {
            return false;
        }
    }
}

IfAddrsConverter* CreateIfAddrsConverter() {
    return new IfAddrsConverter();
}
