project(callee)

#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. AUX_SRC)

include_directories(../../../include/UserService/)
include_directories(../../../include/UserService/protoFile)
include_directories(../../../include/UserService/UserService_Stub)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/UserService/UserService_Stub)

# 指定生成可执行文件
add_executable(callee ${AUX_SRC})

# 指定链接的目录
target_link_libraries(callee protobuf myrpc user_proto muduo_net muduo_base pthread zookeeper_mt sqlpool mysqlclient)