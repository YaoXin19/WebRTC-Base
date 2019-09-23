//
// Created by haha on 9/23/19.
//

#ifndef PTHREAD_NETWORK_H
#define PTHREAD_NETWORK_H

#include "ifaddrs_converter.h"

#include <vector>

#include <sys/types.h>
#include <ifaddrs.h>

class Network {

};

typedef std::vector<Network> NetworkList;

class BasicNetWorkManager {
public:
    bool CreateNetworks(bool include_ignored, NetworkList* networks) const;

    void ConvertIfAddrs(struct ifaddrs* interfaces, IfAddrsConverter* ifaddrs_convertor, bool include_ignored, NetworkList* networks) const;
};

#endif //PTHREAD_NETWORK_H
