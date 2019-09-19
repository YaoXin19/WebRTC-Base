cmake_minimum_required(VERSION 3.14)
project(pthread)

set(CMAKE_CXX_STANDARD 14)

add_executable(incr incr.cpp)

target_link_libraries(
        incr
        -lpthread
)

add_executable(incr_mutex incr_mutex.cpp)
target_link_libraries(
        incr_mutex
        -lpthread
)
