aux_source_directory(. GROUP_PROTO_SRC)

include_directories(../../../include/GroupService/protoFile)

add_library(group_proto STATIC ${GROUP_PROTO_SRC})