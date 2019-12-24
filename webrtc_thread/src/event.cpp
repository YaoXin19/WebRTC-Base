//
// Created by haha on 2019/9/14.
//

#include "event.h"

#include <optional>

#include <errno.h>
#include <time.h>

Event::Event():Event(false, false) {}

Event::Event(bool manual_reset, bool initially_signaled)
    :is_manual_reset_(manual_reset), event_status_(initially_signaled) {
    pthread_mutex_init(&event_mutex_, nullptr);
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    //pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);
    pthread_cond_init(&event_cond_, &cond_attr);
    pthread_condattr_destroy(&cond_attr);
}

Event::~Event() {
    pthread_mutex_destroy(&event_mutex_);
    pthread_cond_destroy(&event_cond_);
}

timespec GetTimespec(const int milliseconds_from_now) {
    timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    ts.tv_sec += (milliseconds_from_now / 1000);
    ts.tv_nsec += (milliseconds_from_now % 1000) * 1000000;

    if (ts.tv_nsec >= 1000000000) {
        ts.tv_sec++;
        ts.tv_nsec -= 1000000000;
    }

    return ts;
}

bool Event::Wait(int give_up_after_ms, int warn_after_ms) {
    const std::optional<timespec> warn_ts =
            warn_after_ms == kForever || (give_up_after_ms != kForever && warn_after_ms > give_up_after_ms)
            ? std::nullopt
            : std::make_optional(GetTimespec(warn_after_ms));

    const std::optional<timespec> give_up_ts =
            give_up_after_ms == kForever
            ? std::nullopt
            : std::make_optional(GetTimespec(give_up_after_ms));

    pthread_mutex_lock(&event_mutex_);
    const auto wait = [&](const std::optional<timespec> timeout_ts){
        int error = 0;
        while (!event_status_ && error==0) {
            if (timeout_ts == std::nullopt) {
                error = pthread_cond_wait(&event_cond_, &event_mutex_);
            } else {
                error = pthread_cond_timedwait(&event_cond_, &event_mutex_, &*timeout_ts);
            }
        }
        return error;
    };

    int error;
    if (warn_ts == std::nullopt) {
        error = wait(give_up_ts);
    } else {
        error = wait(warn_ts);
        if (error == ETIMEDOUT) {
            //
            error = wait(give_up_ts);
        }
    }

    if (error==0 && !is_manual_reset_)
        event_status_ = false;

    pthread_mutex_unlock(&event_mutex_);

    return error==0;
}