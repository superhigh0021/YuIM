project(offlineServer)

#将当前目录下所有文件添加到SRC_LIST
aux_source_directory(. AUX_SRC)

include_directories(../../../include/OfflineService/)
include_directories(../../../include/OfflineService/protoFile)
include_directories(../../../include/OfflineService/OfflineServer)

set(EXECUTABLE_OUTPUT_PATH ../../../../bin/OfflineService/OfflineServer)

# 指定生成可执行文件
add_executable(offlineServer ${AUX_SRC})

# 指定链接的目录
target_link_libraries(offlineServer protobuf myrpc offline_proto muduo_net muduo_base pthread zookeeper_mt sqlpool mysqlclient)