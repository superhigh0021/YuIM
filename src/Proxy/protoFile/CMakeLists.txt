aux_source_directory(. PROXY_PROTO_SRC)

include_directories(../../../include/Proxy/protoFile)

add_library(proxy_proto STATIC ${PROXY_PROTO_SRC})