//
// Created by haha on 9/23/19.
//

#include "network.h"
#include "network_constants.h"

#include <memory>
#include <map>
#include <string>

#include <net/if.h>

AdapterType GetAdaptorTypeFromName(const char* network_name) {
    printf("%s\n", network_name);
    return ADAPTER_TYPE_UNKNOWN;
}

bool BasicNetWorkManager::CreateNetworks(bool include_ignored, NetworkList* networks) const {
    struct ifaddrs* interfaces;
    int error = getifaddrs(&interfaces);
    if (error != 0) {
        return false;
    }

    std::unique_ptr<IfAddrsConverter> ifaddrs_converter(CreateIfAddrsConverter());
    this->ConvertIfAddrs(interfaces, ifaddrs_converter.get(), include_ignored, networks);

    freeifaddrs(interfaces);
    return true;
}

void BasicNetWorkManager::ConvertIfAddrs(struct ifaddrs* interfaces, IfAddrsConverter* ifaddrs_convertor, bool include_ignored, NetworkList* networks) const {
    std::map<std::string, Network*> current_networks;
    for (struct ifaddrs* cursor=interfaces; cursor!=nullptr; cursor=cursor->ifa_next) {

        // Some interface may not have address assigned.
        if (!cursor->ifa_addr || !cursor->ifa_netmask) {
            continue;
        }
        // Skip ones which are down.
        if (!(cursor->ifa_flags & IFF_RUNNING)) {
            continue;
        }
        // Skip unknown family.
        if (cursor->ifa_addr->sa_family != AF_INET &&
                cursor->ifa_addr->sa_family != AF_INET6) {
            continue;
        }
        // Convert to InterfaceAddress.
        InterfaceAddress ip;
        IPAddress mask;
        if (!ifaddrs_convertor->ConvertIfAddrsToIPAddress(cursor, &ip, &mask)) {
            continue;
        }

        AdapterType adapter_type = ADAPTER_TYPE_UNKNOWN;
        if (cursor->ifa_flags & IFF_LOOPBACK) {
            adapter_type = ADAPTER_TYPE_LOOPBACK;
        } else {
            if (false) { // network_monitor_
            }
            if (adapter_type == ADAPTER_TYPE_UNKNOWN) {
                adapter_type = GetAdaptorTypeFromName(cursor->ifa_name);
            }
        }
        int prefix_length;
        IPAddress prefix;
        std::string key; // makenetworkkey

        auto iter = current_networks.find(key);
        if (iter == current_networks.end()) {

        } else {

        }
    }
}
