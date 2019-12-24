//
// Created by haha on 2019/9/16.
//

#ifndef PTHREAD_BYTE_ORDER_H
#define PTHREAD_BYTE_ORDER_H

#include <cstdint>

inline uint16_t HostToNetwork16(uint16_t n) {
    return htobe16(n);
}

#endif //PTHREAD_BYTE_ORDER_H
