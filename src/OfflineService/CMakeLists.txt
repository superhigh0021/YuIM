cmake_minimum_required(VERSION 3.0)
project(offLineService)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

set(EXECUTABLE_OUTPUT_PATH ../../../bin/OfflineService)

# 设置头文件搜索路径
include_directories(../../include/OfflineService)
include_directories(../../include/OfflineService/protoFile)

# 将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(offlineService ${SRC_LIST})

add_subdirectory(OfflineServer)
add_subdirectory(protoFile)

target_link_libraries(offlineService protobuf offline_proto myrpc zookeeper_mt hiredis muduo_net muduo_base pthread)