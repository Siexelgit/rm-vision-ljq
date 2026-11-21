cmake_minimum_required(VERSION 3.10)
project(RmHomework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_library(mylib STATIC src/mean.cpp)

add_executable(test_main main.cpp)

target_link_libraries(test_main mylib)          