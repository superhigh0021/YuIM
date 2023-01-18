project(groupServer)

#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. AUX_SRC)

include_directories(../../../include/GroupService/)
include_directories(../../../include/GroupService/protoFile)
include_directories(../../../include/GroupService/GroupServer)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/GroupService/GroupServer)

# 指定生成可执行文件
add_executable(groupServer ${AUX_SRC})

# 指定链接的目录
target_link_libraries(groupServer protobuf myrpc group_proto muduo_net muduo_base pthread zookeeper_mt sqlpool mysqlclient)