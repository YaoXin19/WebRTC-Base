//
// Created by haha on 2019/9/13.
//

#ifndef PTHREAD_NULL_SOCKET_SERVER_H
#define PTHREAD_NULL_SOCKET_SERVER_H

#include "socket_server.h"

class NullSocketServer : public SocketServer {
public:
    NullSocketServer() {}

    Socket* CreateSocket(int family, int type) {}

    AsyncSocket* CreateAsyncSocket(int family, int type) {}

    bool Wait(int cms, bool process_io) override;

private:
    Event event_;
};

#endif //PTHREAD_NULL_SOCKET_SERVER_H
