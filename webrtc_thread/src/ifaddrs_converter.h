//
// Created by haha on 9/23/19.
//

#ifndef PTHREAD_IFADDRS_CONVERTER_H
#define PTHREAD_IFADDRS_CONVERTER_H

#include "ip_address.h"

class IfAddrsConverter {
public:
    IfAddrsConverter() {}
    virtual ~IfAddrsConverter() {}
    // 注意这里是ifaddrs而不是ifaddr
    virtual bool ConvertIfAddrsToIPAddress(const struct ifaddrs* interface, InterfaceAddress* ipaddress, IPAddress* mask);
};

IfAddrsConverter* CreateIfAddrsConverter();

#endif //PTHREAD_IFADDRS_CONVERTER_H
