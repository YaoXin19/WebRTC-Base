//
// Created by haha on 2019/9/13.
//

#ifndef PTHREAD_SOCKET_SERVER_H
#define PTHREAD_SOCKET_SERVER_H

#include "socket_factory.h"
#include "event.h"

#include <memory>

class SocketServer : public SocketFactory {
public:
    static const int kForever = -1;

    virtual bool Wait(int cms, bool process_io) = 0;

    static std::unique_ptr<SocketServer> CreateDefault();

private:
    Event event_;
};

#endif //PTHREAD_SOCKET_SERVER_H
