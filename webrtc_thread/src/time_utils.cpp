//
// Created by haha on 2019/9/13.
//

#include "time_utils.h"

#include <sys/time.h>
#include <time.h>

static const int64_t kNumMillisecsPerSec = 1000;
static const int64_t kNumNanosecsPerSec = 1000000000;

static const int64_t kNumNanosecsPerMillisec =
        kNumNanosecsPerSec / kNumMillisecsPerSec;

int64_t SystemTimeNanos() {
    int64_t ticks;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    ticks = kNumNanosecsPerSec * static_cast<int64_t>(ts.tv_sec) +
            static_cast<int64_t>(ts.tv_nsec);
    return ticks;
}

int64_t TimeNanos() {
    return SystemTimeNanos();
}

int64_t TimeMillis() {
    return TimeNanos() / kNumNanosecsPerMillisec;
}

int64_t TimeDiff(int64_t later, int64_t earlier) {
    return later - earlier;
}

