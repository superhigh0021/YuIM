aux_source_directory(. SRC_LIST)

add_executable(LogSend ${SRC_LIST})

target_link_libraries(LogSend rpc protobuf muduo_net muduo_base pthread)