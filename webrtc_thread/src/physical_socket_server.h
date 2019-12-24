//
// Created by haha on 2019/9/14.
//

#ifndef PTHREAD_PHYSICAL_SOCKET_SERVER_H
#define PTHREAD_PHYSICAL_SOCKET_SERVER_H

#include "socket_server.h"
#include "../third_party/sigslot.h"
#include "net_helpers.h"

#include <vector>
#include <set>
#include <cassert>

#include <errno.h>
#include <sys/epoll.h>

typedef int SOCKET;

#define INVALID_SOCKET (-1)

class PhysicalSocketServer;

enum DispatcherEvent {
    DE_READ = 0x0001,
    DE_WRITE = 0x0002,
    DE_CONNECT = 0x0004,
    DE_CLOSE = 0x0008,
    DE_ACCEPT = 0x0010
};

class Dispatcher {
public:
    virtual ~Dispatcher() {}

    virtual int GetDescriptor() = 0;
    virtual bool IsDescriptorClosed() = 0;
    virtual uint32_t GetRequestedEvents() = 0;
    virtual void OnReEvent(uint32_t ff) = 0;
    virtual void OnEvent(uint32_t ff, int err) = 0;
};

class PhysicalSocket : public AsyncSocket, public sigslot::has_slots<> {
public:
    PhysicalSocket(PhysicalSocketServer* ss, SOCKET s = INVALID_SOCKET);
    ~PhysicalSocket() override;

    int Bind(const SocketAddress& bind_addr) override; // 实际socket进行bind的地方
    virtual void SetEnabledEvents(uint8_t events);

    // Creates the underlying OS socket (same as the "socket" function)
    virtual bool Create(int family, int type);

    int RecvFrom(void* pv, size_t cb, SocketAddress* paddr, int64_t* timestamp) override;


protected:
    SOCKET s_;
    PhysicalSocketServer* ss_;
    uint8_t enabled_events_;
    ConnState  state_;

private:
    bool udp_;
    int error_;
    AsyncResolver* resolver_;

};

class SocketDispatcher : public Dispatcher, public PhysicalSocket {
public:
    explicit SocketDispatcher(PhysicalSocketServer* ss);
    ~SocketDispatcher() override;

    int GetDescriptor() override;
    bool IsDescriptorClosed() override;
    uint32_t GetRequestedEvents() override;
    void OnReEvent(uint32_t ff) override;
    void OnEvent(uint32_t ff, int err) override;

    bool Create(int family, int type); // 实际创建socket
    bool Initialize(); // 将socket加入epoll


};

class PhysicalSocketServer : public SocketServer {
public:
    PhysicalSocketServer();
    ~PhysicalSocketServer() override;

    Socket* CreateSocket(int family, int type) { assert(false); }

    AsyncSocket* CreateAsyncSocket(int family, int type);

    bool Wait(int cms, bool process_io) override;

    void Add(Dispatcher* pdispatcher);

private:
    void AddEpoll(Dispatcher* dispatcher);
    bool WaitEpoll(int cmsWait);

private:
    typedef std::set<Dispatcher*> DispatcherSet;
private:
    int epoll_fd_ = INVALID_SOCKET;
    std::vector<struct epoll_event> epoll_events_;
    DispatcherSet dispatchers_;
    bool fWait_;
};

#endif //PTHREAD_PHYSICAL_SOCKET_SERVER_H
