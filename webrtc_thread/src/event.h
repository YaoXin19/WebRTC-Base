//
// Created by haha on 2019/9/14.
//

#ifndef PTHREAD_EVENT_H
#define PTHREAD_EVENT_H

#include <pthread.h>

class Event {
public:
    static const int kForever = -1;

    Event();
    Event(bool manual_reset, bool initially_signaled);
    ~Event();

    bool Wait(int give_up_after_time, int warn_after_ms);

private:
    pthread_mutex_t event_mutex_;
    pthread_cond_t event_cond_;
    const bool is_manual_reset_;
    bool event_status_;
};

#endif //PTHREAD_EVENT_H
