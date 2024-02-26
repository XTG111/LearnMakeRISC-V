cmake_minimum_required(VERSION 3.10)
project(crvemu)

set(CMAKE_CXX_STANDARD 11)

set( SRC_LIST
     ./main.cpp
     ./thirdparty/Self_CPU.cpp)

add_executable(crvemu ${SRC_LIST})

