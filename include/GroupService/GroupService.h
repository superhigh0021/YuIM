#include "protoFile/LogServer.pb.h"
#include "protoFile/GroupServer.pb.h"
#include "protoFile/GroupService.pb.h"

#include "ZookeeperMaster.h"

#include <myrpc/myrpcchannel.h>
#include <myrpc/myrpcchannel.h>
#include <google/protobuf/service.h>

#include <string>

using namespace std;

class GroupService : public ik_GroupService::GroupServiceRpc {
public:
    GroupService();

public:
    void addGroup(::google::protobuf::RpcController* controller,
                  const ::ik_GroupService::AddGroupRequest* request,
                  ::google::protobuf::Empty* response,
                  ::google::protobuf::Closure* done);
    void createGroup(::google::protobuf::RpcController* controller,
                     const ::ik_GroupService::CreateGroupRequest* request,
                     ::ik_GroupService::CreateGroupResponse* response,
                     ::google::protobuf::Closure* done);
    void quitGroup(::google::protobuf::RpcController* controller,
                   const ::ik_GroupService::QuitGroupRequest* request,
                   ::google::protobuf::Empty* response,
                   ::google::protobuf::Closure* done);
    void getGroupUsers(::google::protobuf::RpcController* controller,
                       const ::ik_GroupService::GetGroupUsersRequest* request,
                       ::ik_GroupService::GetGroupUsersResponse* response,
                       ::google::protobuf::Closure* done);

private:
    ik::LogServerRpc_Stub stub_;

    ZKMaster master_;
};