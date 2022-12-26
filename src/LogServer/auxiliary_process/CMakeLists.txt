aux_source_directory(. SRC_LIST)

add_executable(LogSend ${SRC_LIST})

include_directories(../../../include/LogServer/auxiliary_process)

target_link_libraries(LogSend protobuf muduo_net muduo_base pthread)
# target_link_libraries(LogSend rpc protobuf muduo_net muduo_base pthread)