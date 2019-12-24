//
// Created by haha on 9/23/19.
//

#ifndef PTHREAD_NETWORK_H
#define PTHREAD_NETWORK_H

#include "ifaddrs_converter.h"
#include "network_constants.h"

#include <vector>
#include <string>

#include <sys/types.h>
#include <ifaddrs.h>

class Network {
public:
    Network(const std::string& name,
            const std::string& description,
            const IPAddress& prefix,
            int prefix_length,
            AdapterType type);

private:
    std::string name_;
    std::string description_;
    IPAddress prefix_;
    int prefix_length_;
    AdapterType  type_;
};

typedef std::vector<Network*> NetworkList;

class BasicNetWorkManager {
public:
    bool CreateNetworks(bool include_ignored, NetworkList* networks) const;

    void ConvertIfAddrs(struct ifaddrs* interfaces, IfAddrsConverter* ifaddrs_convertor, bool include_ignored, NetworkList* networks) const;
};



#endif //PTHREAD_NETWORK_H
