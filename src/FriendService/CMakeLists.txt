cmake_minimum_required(VERSION 3.0)
project(friendService)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

set(EXECUTABLE_OUTPUT_PATH ../../../bin/FriendService)

# 设置头文件搜索路径
include_directories(../../include/FriendService)
include_directories(../../include/FriendService/protoFile)

# 将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(friendService ${SRC_LIST})

add_subdirectory(FriendServer)
add_subdirectory(protoFile)
add_subdirectory(example)

target_link_libraries(friendService protobuf friend_proto myrpc zookeeper_mt hiredis muduo_net muduo_base pthread)