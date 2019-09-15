//
// Created by haha on 2019/9/13.
//

#ifndef PTHREAD_MESSAGE_QUEUE_H
#define PTHREAD_MESSAGE_QUEUE_H

#include <queue>
#include <list>
#include <memory>

#include "socket_server.h"

struct Message {
    void* posted_from;
    void* phandler;
    void* message_id;
    void* pdata;
    void* ts_sensitive;
};

typedef std::list<Message> MessageList;

struct DelayedMessage {
    bool operator<(const DelayedMessage& dmsg) const {
        return (dmsg.msTrigger_<msTrigger_) ||
                ((dmsg.msTrigger_==msTrigger_) && (dmsg.num_<num_));
    }
    void* cmsDelay_;
    int64_t msTrigger_;
    uint32_t num_;
    Message msg_;
};

class MessageQueue {
public:
    static const int kForever = -1;

    MessageQueue(SocketServer* ss, bool init_queue);

    MessageQueue(std::unique_ptr<SocketServer> ss, bool init_queue);

    bool Get(Message* pmsg, int cmsWait, bool process_io=true);

    SocketServer* socketserver();

        protected:
    class PriorityQueue : public std::priority_queue<DelayedMessage> {
    public:
        container_type& container() { return c; }
        void reheap() { make_heap(c.begin(), c.end(), comp); }
    };

private:
    PriorityQueue dmsgq_; // delay message queue
    MessageList msgq_;

    SocketServer* const ss_;
    std::unique_ptr<SocketServer> own_ss_;
};

#endif //PTHREAD_MESSAGE_QUEUE_H
