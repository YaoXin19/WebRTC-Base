//
// Created by haha on 2019/9/15.
//

#include "socket_address.h"
#include "byte_order.h"

#include <cassert>

SocketAddress& SocketAddress::operator=(const SocketAddress& addr) {
    ip_ = addr.ip_;
    hostname_ = addr.hostname_;
    port_ = addr.port_;
    scope_id_ = addr.scope_id_;
    literal_ = addr.literal_;
    return *this;
}


bool SocketAddress::FromString(const std::string& str) {
    std::string::size_type pos = str.find(':');
    if (std::string::npos == pos)
        return false;
    SetPort(strtoul(str.substr(pos + 1).c_str(), nullptr, 10));
    SetIP(str.substr(0, pos));
}

void SocketAddress::SetIP(const std::string& hostname) {
    hostname_ = hostname;
    literal_ = IPFromString(hostname, &ip_);
    if (!literal_) {
        ip_ = IPAddress();
    }
    scope_id_ = 0;
}

void SocketAddress::SetPort(int port) {
    port_ = static_cast<uint16_t>(port);
    int a = 10;
}

static size_t ToSockAddrStorageHelper(sockaddr_storage* addr, IPAddress ip, uint16_t port, int scope_id) {
    memset(addr, 0, sizeof(sockaddr_storage));
    addr->ss_family = static_cast<unsigned short>(ip.family());
    if (addr->ss_family == AF_INET6) {
        assert(false);
    } else if (addr->ss_family == AF_INET) {
        sockaddr_in* saddr = reinterpret_cast<sockaddr_in*>(addr);
        saddr->sin_addr = ip.ipv4_address();
        saddr->sin_port = HostToNetwork16(port);
        return sizeof(sockaddr_in);
    }
    return 0;
}

size_t SocketAddress::ToSockAddrStorage(sockaddr_storage* addr) {
    return ToSockAddrStorageHelper(addr, ip_, port_, scope_id_);
}
