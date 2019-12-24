//
// Created by haha on 2019/9/14.
//

#include "null_socket_server.h"

bool NullSocketServer::Wait(int cms, bool process_io) {
    event_.Wait(cms, Event::kForever);
    return true;
}