aux_source_directory(. USER_PROTO_SRC)

include_directories(../../../include/UserService/protoFile)

add_library(user_proto STATIC ${USER_PROTO_SRC})