project(userServer)

#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. AUX_SRC)

include_directories(../../../include/UserService/)
include_directories(../../../include/UserService/protoFile)
include_directories(../../../include/UserService/UserServer)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/UserService/UserServer)

# 指定生成可执行文件
add_executable(userServer ${AUX_SRC})

# 指定链接的目录
target_link_libraries(userServer protobuf myrpc user_proto muduo_net muduo_base pthread zookeeper_mt sqlpool mysqlclient)