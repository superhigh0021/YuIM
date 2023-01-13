aux_source_directory(. SRC_LIST)

add_executable(LogSend ${SRC_LIST})

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ../../../../bin/LogServer/auxiliary_process)

include_directories(../../../include/LogServer/auxiliary_process)
include_directories(../../../include/LogServer/protoFile)

# target_link_libraries(LogSend protobuf muduo_net muduo_base pthread)
target_link_libraries(LogSend myrpc protobuf muduo_net muduo_base pthread)
