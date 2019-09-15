//
// Created by haha on 2019/9/15.
//

#ifndef PTHREAD_IP_ADDRESS_H
#define PTHREAD_IP_ADDRESS_H

#include <netinet/in.h>

#include <cstring>
#include <string>

class IPAddress {
public:
    IPAddress() : family_(AF_UNSPEC) { ::memset(&u_, 0, sizeof(u_)); }

    explicit IPAddress(const in_addr& ip4) : family_(AF_INET) {
        ::memset(&u_, 0, sizeof(u_));
        u_.ip4 = ip4;
    }

    int family() const { return family_; }

    in_addr ipv4_address() const;

private:
    int family_;
    union {
        in_addr ip4;
        in6_addr ip6;
    } u_;
};

bool IPFromString(const std::string& str, IPAddress* out);

#endif //PTHREAD_IP_ADDRESS_H
