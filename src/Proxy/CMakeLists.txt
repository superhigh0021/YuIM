cmake_minimum_required(VERSION 3.0)
project(ProxyServer)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

set(EXECUTABLE_OUTPUT_PATH ../../bin/Proxy)

include_directories(../../include/Proxy)
include_directories(../../include/Proxy/protoFile)

aux_source_directory(. SRC_LIST)
aux_source_directory(./proto PROTO_LIST)

add_executable(ProxyServer ${SRC_LIST} ${PROTO_LIST})

target_link_libraries(ProxyServer protobuf myrpc zookeeper_mt hiredis muduo_net muduo_base pthread)
