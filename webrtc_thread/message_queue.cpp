//
// Created by haha on 2019/9/13.
//
#include "message_queue.h"
#include "time_utils.h"

#include <cstdint>

MessageQueue::MessageQueue(SocketServer* ss, bool init_queue)
    :ss_(ss) {
}


MessageQueue::MessageQueue(std::unique_ptr<SocketServer> ss, bool init_queue)
: MessageQueue(ss.get(), init_queue) {
    own_ss_ = std::move(ss);
}


bool MessageQueue::Get(Message* pmsg, int cmsWait, bool process_io) {

    int64_t msStart = TimeMillis();
    int64_t msCurrent = msStart;

    while (true) { // 循环1：同时处理 消息队列 和 IO

        int64_t cmsDelayNext = kForever; // 距离下次DelayMessageQueue出发的时间
        bool first_pass = true;
        while (true) { // 循环2：处理 消息队列(DelayMessageQueue+MessageQueue)
            {
                if (first_pass) { // DelayMessageQueue只处理一次
                    first_pass = false;
                    while (!dmsgq_.empty()) { // 循环3：处理DelayMessageQueue
                        if (msCurrent < dmsgq_.top().msTrigger_) { // 如果消息的触发时间还没有到，则跳出循环
                            cmsDelayNext = TimeDiff(dmsgq_.top().msTrigger_, msCurrent); // later - earlier
                            break;
                        }
                        msgq_.push_back(dmsgq_.top().msg_); // 否则，将DelayMessageQueue中出发时间已经到了消息放入MessageQueue中
                        dmsgq_.pop();
                    }
                }

                if (msgq_.empty()) { // 如果MessageQueue为空，则跳出循环, 去处理IO
                    break;
                } else {
                    *pmsg = msgq_.front();
                    msgq_.pop_front();
                }

                return true; // 如果MessageQueue不为空，则取出最近的，返回，不处理IO
            }
        }

        int64_t cmsNext;
        if (cmsWait == kForever) {
            cmsNext = cmsDelayNext;
        } else {

        }

        {
            if (!ss_->Wait(static_cast<int>(cmsNext), process_io))
                return false;
        }
    }

    return false;
}

SocketServer* MessageQueue::socketserver() {
    return ss_;
}
