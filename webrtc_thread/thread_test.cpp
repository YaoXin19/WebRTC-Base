//
// Created by haha on 2019/9/13.
//

#include "thread.h"
#include "socket_address.h"
#include "async_udp_socket.h"

int main() {
    //std::unique_ptr<Thread> thread = Thread::Create();
    //thread->Start();

    SocketAddress server_addr;
    //server_addr.FromString("127.0.0.1:8888");
    server_addr.FromString("192.168.1.166:8888");

    Thread* pthMain = Thread::Current();

    AsyncUDPSocket* server_scoket =
            AsyncUDPSocket::Create(pthMain->socketserver(), server_addr);

    pthMain->Run();

    return 0;
}


