#include "LogServer.pb.h"
#include "protoFile/OfflineServer.pb.h"
#include "protoFile/OfflineService.pb.h"

#include "ZookeeperMaster.h"

#include <google/protobuf/service.h>
#include <myrpc/myrpcchannel.h>
#include <myrpc/myrpccontroller.h>

#include <string>

using namespace std;
class OfflineService : public ik_OfflineService::OfflineServiceRpc {
public:
    OfflineService();

public:
    void WriteOffline(::google::protobuf::RpcController* controller,
                      const ::ik_OfflineService::WriteOfflineRequest* request,
                      ::google::protobuf::Empty* response,
                      ::google::protobuf::Closure* done);
    void ReadOffline(::google::protobuf::RpcController* controller,
                     const ::ik_OfflineService::ReadOfflineRequest* request,
                     ::ik_OfflineService::ReadOfflineResponse* response,
                     ::google::protobuf::Closure* done);

private:
    ik::LogServerRpc_Stub stub_;

    ZKMaster master_;
};