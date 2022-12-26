cmake_minimum_required(VERSION 3.0)

project(LogServer)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

set(EXECUTABLE_OUTPUT_PATH ../../bin)

# 这个可以在cmake25.1版本使用，很方便
# include_directories(${PARENT_DIRECTORY}/include/LogServer)
include_directories(../../include/LogServer)

# 这句写的有问题，等后面改
link_directories(../../third_party)

add_subdirectory(auxiliary_process)