//
// Created by haha on 2019/9/13.
//

#ifndef PTHREAD_SOCKET_FACTORY_H
#define PTHREAD_SOCKET_FACTORY_H

#include "async_socket.h"

class SocketFactory {
public:
    virtual ~SocketFactory() {}

    virtual Socket* CreateSocket(int family, int type) = 0;

    virtual AsyncSocket* CreateAsyncSocket(int family, int type) = 0;

};

#endif //PTHREAD_SOCKET_FACTORY_H
