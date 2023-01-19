cmake_minimum_required(VERSION 3.0)
project(userService)

# 编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

set(EXECUTABLE_OUTPUT_PATH ../../../bin/UserService)

include_directories(../../include/UserService)
include_directories(../../include/UserService/protoFile)

# 将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. SRC_LIST)

add_subdirectory(protoFile)
add_subdirectory(UserServer)
add_subdirectory(example)

# 指定生成可执行文件
add_executable(userService ${SRC_LIST})

# 指定链接的目录
target_link_libraries(userService protobuf myrpc user_proto muduo_net muduo_base pthread zookeeper_mt sqlpool mysqlclient)