//
// Created by haha on 2019/9/14.
//

#include "physical_socket_server.h"

#include <memory>
#include <cassert>

#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>


static const size_t kInitialEpollEvents = 128;

static const size_t kMaxEpollEvents = 8192;

typedef void* SockOptArg;

std::unique_ptr<SocketServer> SocketServer::CreateDefault() {
    return std::unique_ptr<SocketServer>(new PhysicalSocketServer);
}

static void ProcessEvents(Dispatcher* dispatcher, bool readable, bool writable, bool check_error) {
    int errcode = 0;
    if (check_error) {
        socklen_t len = sizeof(errcode);
        ::getsockopt(dispatcher->GetDescriptor(), SOL_SOCKET, SO_ERROR, &errcode, &len);
    }

    uint32_t ff = 0;
    if (readable) {
        if (dispatcher->GetRequestedEvents() & DE_ACCEPT) {
            ff |= DE_ACCEPT;
        //} else if () {

        //} else {

        }
    }
}

PhysicalSocket::PhysicalSocket(PhysicalSocketServer* ss, SOCKET s)
        : ss_(ss),
          s_(s),
          error_(0),
          state_((s == INVALID_SOCKET) ? CS_CLOSED : CS_CONNECTED),
          resolver_(nullptr) {
    if (s_ != INVALID_SOCKET) {
        SetEnabledEvents(DE_READ | DE_WRITE);

        int type = SOCK_STREAM;
        socklen_t len = sizeof(type);
        const int res =
                getsockopt(s_, SOL_SOCKET, SO_TYPE, (SockOptArg)&type, &len);
        //RTC_DCHECK_EQ(0, res);
        udp_ = (SOCK_DGRAM == type);
    }
}

void Close() {
    assert(false);
}

PhysicalSocket::~PhysicalSocket() {
    Close();
}

int PhysicalSocket::Bind(const SocketAddress& bind_addr) {
    SocketAddress copied_bind_addr = bind_addr;
    sockaddr_storage addr_storage;
    size_t len = copied_bind_addr.ToSockAddrStorage(&addr_storage);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&addr_storage);
    int err = ::bind(s_, addr, static_cast<int>(len));
    // UpdateLastError();
    return err;
}


void PhysicalSocket::SetEnabledEvents(uint8_t events) {
    enabled_events_ = events;
}

bool PhysicalSocket::Create(int family, int type) {
    // Close();
    s_ = ::socket(family, type, 0);
    udp_ = (SOCK_DGRAM == type);
    //UpdateLastError();
    if (udp_) {
        SetEnabledEvents(DE_READ | DE_WRITE);
    }
    return s_ != INVALID_SOCKET;
}

SocketDispatcher::SocketDispatcher(PhysicalSocketServer* ss)
        : PhysicalSocket(ss)
{
}

SocketDispatcher::~SocketDispatcher() {
    Close();
}

bool SocketDispatcher::Create(int family, int type) {
    // Change the socket to be non-blocking.
    if (!PhysicalSocket::Create(family, type))
        return false;

    if (!Initialize())
        return false;

    return true;
}

bool SocketDispatcher::Initialize() {
    // RTC_DCHECK(s_ != INVALID_SOCKET);
    // Must be a non-blocking
    fcntl(s_, F_SETFL, fcntl(s_, F_GETFL, 0) | O_NONBLOCK);
    ss_->Add(this);
    return true;
}

int SocketDispatcher::GetDescriptor() {
    return s_; // 从PhysicalSocket中返回
}

bool SocketDispatcher::IsDescriptorClosed() {assert(false);}

uint32_t SocketDispatcher::GetRequestedEvents() {
    return enabled_events_;
}


PhysicalSocketServer::PhysicalSocketServer() : fWait_(false) {
    epoll_fd_ = epoll_create(FD_SETSIZE);
    if (-1 == epoll_fd_) {
        epoll_fd_ = INVALID_SOCKET;
    }
}

PhysicalSocketServer::~PhysicalSocketServer() {
    if (epoll_fd_ != INVALID_SOCKET) {
        close(epoll_fd_);
    }
}

bool PhysicalSocketServer::Wait(int cmsWait, bool process_io) {
    if (!process_io) {
        //return WaitPoll();
    } else if (epoll_fd_ != INVALID_SOCKET) {
        return this->WaitEpoll(cmsWait);
    }

    assert(false);
}

void PhysicalSocketServer::Add(Dispatcher* pdispatcher) {
    // 加锁
    if (epoll_fd_ != INVALID_SOCKET)
        AddEpoll(pdispatcher);
}

static int GetEpollEvents(uint32_t ff) {
    int events = 0;
    if (ff & (DE_READ | DE_ACCEPT))
        events |= EPOLLIN;
    if (ff & (DE_WRITE | DE_CONNECT))
        events |= EPOLLOUT;
    return events;
}

void PhysicalSocketServer::AddEpoll(Dispatcher* dispatcher) {
    int fd = dispatcher->GetDescriptor();
    if (fd == INVALID_SOCKET)
        return;

    struct epoll_event event = {0};
    event.events = GetEpollEvents(dispatcher->GetRequestedEvents());
    event.data.ptr = dispatcher;
    int err = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event);
    if (err == -1) {

    }
}

bool PhysicalSocketServer::WaitEpoll(int cmsWait) {
    int64_t tvWait = -1;
    int64_t tvStop = -1;

    if (epoll_events_.empty()) {
        epoll_events_.resize(kInitialEpollEvents);
    }

    fWait_ = true;

    while (fWait_) {
        int n = epoll_wait(epoll_fd_, &epoll_events_[0],
                           static_cast<int>(epoll_events_.size()),
                           static_cast<int>(tvWait));

        if (n < 0) {

        } else if (n == 0) {
            return true;
        } else {
            for (int i=0; i<n; ++i) {

                const epoll_event& event = epoll_events_[i];
                Dispatcher* pdispatcher = static_cast<Dispatcher*>(event.data.ptr);
                if (dispatchers_.find(pdispatcher) == dispatchers_.end()) {
                    continue;
                }

                bool readable = (event.events & (EPOLLIN | EPOLLPRI));
                bool writable = (event.events & EPOLLOUT);
                bool check_error = (event.events & (EPOLLRDHUP | EPOLLERR | EPOLLHUP));

                ProcessEvents(pdispatcher, readable, writable, check_error);
            }
        }

        if (static_cast<size_t>(n) == epoll_events_.size() &&
            epoll_events_.size() < kMaxEpollEvents) {
            epoll_events_.resize(std::max(epoll_events_.size()*2, kMaxEpollEvents));
        }

        if (cmsWait != kForever) {

        }
    }

    return true;
}

AsyncSocket* PhysicalSocketServer::CreateAsyncSocket(int family, int type) {
    SocketDispatcher* dispatcher = new SocketDispatcher(this);
    if (dispatcher->Create(family, type)) {
        return dispatcher;
    } else {
        delete dispatcher;
        return nullptr;
    }
}
