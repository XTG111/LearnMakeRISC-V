cmake_minimum_required(VERSION 3.22)
project(crvemu)

set(CMAKE_CXX_STANDARD 17)

set(COMMON_SOURCES
     ./thirdparty/DramType.h
     ./thirdparty/Exception.h
     ./thirdparty/Self_Bus.h
     ./thirdparty/Self_CPU.h
     ./thirdparty/Self_DRAM.h
     ./thirdparty/Self_CPU.cpp
     ./thirdparty/Self_Bus.cpp
     ./thirdparty/Self_DRAM.cpp
     ./thirdparty/Exception.cpp
)

add_library(common_library ${COMMON_SOURCES})

set( SRC_LIST
     ./main.cpp
)

add_executable(crvemu ${SRC_LIST})

target_link_libraries(crvemu common_library)

