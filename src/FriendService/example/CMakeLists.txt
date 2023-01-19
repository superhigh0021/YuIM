#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. FRIEND)

include_directories(../../../include/FriendService)
include_directories(../../../include/FriendService/protoFile)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/FriendService/example)

# 指定生成可执行文件
add_executable(friend_example ${FRIEND})

# 指定链接的目录
target_link_libraries(friend_example protobuf myrpc friend_proto muduo_net muduo_base pthread zookeeper_mt)