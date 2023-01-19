project(friendServer)

#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. AUX_SRC)

include_directories(../../../include/FriendService/)
include_directories(../../../include/FriendService/protoFile)
include_directories(../../../include/FriendService/FriendServer)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/FriendService/FriendServer)

# 指定生成可执行文件
add_executable(friendServer ${AUX_SRC})

# 指定链接的目录
target_link_libraries(friendServer protobuf myrpc friend_proto muduo_net muduo_base pthread zookeeper_mt sqlpool mysqlclient)