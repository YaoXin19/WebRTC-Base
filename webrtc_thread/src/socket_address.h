//
// Created by haha on 2019/9/15.
//

#ifndef PTHREAD_SOCKET_ADDRESS_H
#define PTHREAD_SOCKET_ADDRESS_H

#include <string>

#include "ip_address.h"

class SocketAddress {
public:
    SocketAddress& operator=(const SocketAddress& addr);

    // Parses hostname:port and [hostname]:port.
    bool FromString(const std::string& str);

    void SetPort(int port);

    void SetIP(const std::string& hostname);

    int family() const { return ip_.family(); }

    size_t ToSockAddrStorage(sockaddr_storage* addr);

private:
    IPAddress ip_;

    std::string hostname_;
    uint16_t port_;
    int scope_id_;
    bool literal_;

};

#endif //PTHREAD_SOCKET_ADDRESS_H
