//
// Created by haha on 2019/9/15.
//

#include "net_helpers.h"

#include <arpa/inet.h>

namespace rtc {
    int inet_pton(int af, const char* src, void* dst) {
        return ::inet_pton(af, src, dst);
    }
}
