#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. EXAMPLE)

include_directories(../../../include/UserService)
include_directories(../../../include/UserService/protoFile)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/UserService/example)

# 指定生成可执行文件
add_executable(callee_example ${EXAMPLE})

# 指定链接的目录
target_link_libraries(callee_example protobuf myrpc user_proto muduo_net muduo_base pthread zookeeper_mt)