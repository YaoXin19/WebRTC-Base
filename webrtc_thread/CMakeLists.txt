cmake_minimum_required(VERSION 3.14)
project(pthread)

set(CMAKE_CXX_STANDARD 17)


# USE_CLOCK_GETTIME 1
# USE_PTHREAD_COND_TIMEDWAIT_MONOTONIC_NP 0

#add_executable(incr incr.cpp thread.h thread.cpp)

#target_link_libraries(
#        incr
#        -lpthread
#)

#add_executable(incr_mutex incr_mutex.cpp)
#target_link_libraries(
#        incr_mutex
#        -lpthread
#)

#add_executable(udp_client udp_client.cpp)
#target_link_libraries(
#        udp_client
#        -lpthread
#)

#add_executable(
#        thread_test
#        thread_test.cpp
#        sigslot.cc
#        thread.cpp
#        message_queue.cpp
#        time_utils.cpp event.cpp event.h null_socket_server.cpp physical_socket_server.cpp physical_socket_server.h socket_address.cpp socket_address.h async_udp_socket.cpp async_udp_socket.h async_packet_socket.cpp async_packet_socket.h socket.cpp socket.h async_socket.cpp async_socket.h ip_address.cpp ip_address.h net_helpers.cpp net_helpers.h byte_order.h network.cpp network.h ifaddrs_converter.cpp ifaddrs_converter.h network_constants.h)
#target_link_libraries(
#        thread_test
#        -lpthread
#)
#
#add_executable(
#        network_unittest
#        network_unittest.cpp
#        network.cpp
#        ifaddrs_converter.cpp ifaddrs_converter.h)

add_library(
        webrtc_base
        STATIC
        third_party/sigslot.cc
        src/thread.cpp
        src/message_queue.cpp
        src/time_utils.cpp
        src/event.cpp
        src/null_socket_server.cpp
        src/physical_socket_server.cpp
        src/socket_address.cpp
        src/async_udp_socket.cpp
        src/async_packet_socket.cpp
        src/async_socket.cpp
        src/ip_address.cpp
        src/net_helpers.cpp
        src/network.cpp
        src/ifaddrs_converter.cpp
)

target_link_libraries(
        webrtc_base
        -lpthread
)

add_executable(
        stunserver
        test/stunserver_main.cpp
)

target_link_libraries(
        stunserver
        webrtc_base
)
