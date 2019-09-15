//
// Created by haha on 2019/9/15.
//

#include "async_udp_socket.h"


static const int BUF_SIZE = 64 * 1024;

AsyncUDPSocket* AsyncUDPSocket::Create(AsyncSocket* socket,
                                       const SocketAddress& bind_address) {
    std::unique_ptr<AsyncSocket> owned_socket(socket);
    if (socket->Bind(bind_address) < 0) {
        //RTC_LOG(LS_ERROR) << "Bind() failed with error " << socket->GetError();
        return nullptr;
    }
    return new AsyncUDPSocket(owned_socket.release());
}

AsyncUDPSocket* AsyncUDPSocket::Create(SocketFactory* factory,
                                       const SocketAddress& bind_address) {
    AsyncSocket* socket =
            factory->CreateAsyncSocket(bind_address.family(), SOCK_DGRAM);
    if (!socket)
        return nullptr;
    return Create(socket, bind_address);
}

AsyncUDPSocket::AsyncUDPSocket(AsyncSocket* socket) : socket_(socket) {
    size_ = BUF_SIZE;
    buf_ = new char[size_];

    // The socket should start out readable but not writable.
    //socket_->SignalReadEvent.connect(this, &AsyncUDPSocket::OnReadEvent);
    //socket_->SignalWriteEvent.connect(this, &AsyncUDPSocket::OnWriteEvent);
}

AsyncUDPSocket::~AsyncUDPSocket() {
    delete[] buf_;
}