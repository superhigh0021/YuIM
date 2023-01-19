aux_source_directory(. FRIEND_PROTO_SRC)

include_directories(../../../include/FriendService/protoFile)

add_library(friend_proto STATIC ${FRIEND_PROTO_SRC})