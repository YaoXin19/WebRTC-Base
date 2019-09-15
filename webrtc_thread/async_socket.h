//
// Created by haha on 2019/9/15.
//

#ifndef PTHREAD_ASYNC_SOCKET_H
#define PTHREAD_ASYNC_SOCKET_H

#include "socket.h"

class AsyncSocket : public Socket {
public:
    ~AsyncSocket() override;
};

#endif //PTHREAD_ASYNC_SOCKET_H
