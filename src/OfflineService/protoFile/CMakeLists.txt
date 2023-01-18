aux_source_directory(. OFFLINE_PROTO_SRC)

include_directories(../../../include/OfflineService/protoFile)

add_library(offline_proto STATIC ${OFFLINE_PROTO_SRC})