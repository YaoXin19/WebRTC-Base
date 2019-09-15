//
// Created by haha on 2019/9/15.
//

#ifndef PTHREAD_SOCKET_H
#define PTHREAD_SOCKET_H

#include "socket_address.h"

class Socket {
public:
    enum ConnState {CS_CLOSED, CS_CONNECTING, CS_CONNECTED};
public:
    virtual ~Socket() {}

    virtual int Bind(const SocketAddress& addr) = 0;
};

#endif //PTHREAD_SOCKET_H
