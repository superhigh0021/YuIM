cmake_minimum_required(VERSION 3.0)
project(groupService)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

set(EXECUTABLE_OUTPUT_PATH ../../../bin/GroupService)

# 设置头文件搜索路径
include_directories(../../include/GroupService)
include_directories(../../include/GroupService/protoFile)

# 将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(groupService ${SRC_LIST})

add_subdirectory(GroupServer)
add_subdirectory(protoFile)

target_link_libraries(groupService protobuf group_proto myrpc zookeeper_mt hiredis muduo_net muduo_base pthread)