cmake_minimum_required(VERSION 3.14)
project(pthread)

set(CMAKE_CXX_STANDARD 17)


# USE_CLOCK_GETTIME 1
# USE_PTHREAD_COND_TIMEDWAIT_MONOTONIC_NP 0

add_executable(incr incr.cpp thread.h thread.cpp)

target_link_libraries(
        incr
        -lpthread
)

add_executable(incr_mutex incr_mutex.cpp)
target_link_libraries(
        incr_mutex
        -lpthread
)

add_executable(
        thread_test
        thread_test.cpp
        sigslot.cc
        thread.cpp
        message_queue.cpp
        time_utils.cpp event.cpp event.h null_socket_server.cpp physical_socket_server.cpp physical_socket_server.h socket_address.cpp socket_address.h async_udp_socket.cpp async_udp_socket.h async_packet_socket.cpp async_packet_socket.h socket.cpp socket.h async_socket.cpp async_socket.h ip_address.cpp ip_address.h net_helpers.cpp net_helpers.h byte_order.h)
target_link_libraries(
        thread_test
        -lpthread
)

