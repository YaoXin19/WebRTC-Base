//
// Created by haha on 2019/9/15.
//

#ifndef PTHREAD_ASYNC_UDP_SOCKET_H
#define PTHREAD_ASYNC_UDP_SOCKET_H

#include "async_packet_socket.h"
#include "socket_factory.h"
#include "socket_address.h"

#include <memory>

class AsyncUDPSocket : public AsyncPacketSocket {
public:
    // Binds |socket| and creates AsyncUDPSocket for it. Takes ownership
    // of |socket|. Returns null if bind() fails (|socket| is destroyed
    // in that case).
    static AsyncUDPSocket* Create(AsyncSocket* socket,
                                  const SocketAddress& bind_address);
    // Creates a new socket for sending asynchronous UDP packets using an
    // asynchronous socket from the given factory.
    static AsyncUDPSocket* Create(SocketFactory* factory,
                                  const SocketAddress& bind_address);

    explicit AsyncUDPSocket(AsyncSocket* socket);
    ~AsyncUDPSocket() override;

private:
    void OnReadEvent(AsyncSocket* socket);

private:
    std::unique_ptr<AsyncSocket> socket_;
    char* buf_;
    size_t size_;
};

#endif //PTHREAD_ASYNC_UDP_SOCKET_H
