//
// Created by haha on 2019/9/13.
//

#ifndef PTHREAD_TIME_UTILS_H
#define PTHREAD_TIME_UTILS_H

#include <cstdint>

int64_t TimeMillis();

int64_t TimeDiff(int64_t later, int64_t earlier);

#endif //PTHREAD_TIME_UTILS_H
