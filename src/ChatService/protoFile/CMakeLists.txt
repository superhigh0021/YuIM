aux_source_directory(. CHAT_PROTO_SRC)

include_directories(../../../include/ChatService/protoFile)

add_library(chat_proto STATIC ${CHAT_PROTO_SRC})