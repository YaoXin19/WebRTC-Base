//
// Created by haha on 2019/9/15.
//

#ifndef PTHREAD_ASYNC_SOCKET_H
#define PTHREAD_ASYNC_SOCKET_H

#include "socket.h"
#include "sigslot.h"


class AsyncSocket : public Socket {
public:
    ~AsyncSocket() override;

    sigslot::signal1<AsyncSocket*, sigslot::multi_threaded_local> SignalReadEvent;
};

#endif //PTHREAD_ASYNC_SOCKET_H
