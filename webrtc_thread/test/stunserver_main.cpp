//
// Created by haha on 2019/9/13.
//

#include "../src/thread.h"
#include "../src/socket_address.h"
#include "../src/async_udp_socket.h"

int main() {

    SocketAddress server_addr;
    server_addr.FromString("192.168.1.166:8888");

    Thread* pthMain = Thread::Current();

    AsyncUDPSocket* server_scoket =
            AsyncUDPSocket::Create(pthMain->socketserver(), server_addr);

    pthMain->Run();

    return 0;
}
