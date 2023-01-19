#pragma once

#include "protoFile/LogServer.pb.h"
#include "protoFile/FriendServer.pb.h"
#include "protoFile/FriendService.pb.h"
#include "ZookeeperMaster.h"

#include <google/protobuf/empty.pb.h>
#include <google/protobuf/service.h>

#include <myrpc/myrpcchannel.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

class FriendService : public ik_FriendService::FriendServiceRpc {
public:
    FriendService();

public:
    // 获取好友列表
    void getFriendList(::google::protobuf::RpcController* controller,
                       const ::ik_FriendService::FriendListRequest* request,
                       ::ik_FriendService::FriendListResponse* response,
                       ::google::protobuf::Closure* done);

    // 获取用户信息
    void getUserInfo(::google::protobuf::RpcController* controller,
                     const ::ik_FriendService::UserInfoRequest* request,
                     ::ik_FriendService::UserInfoResponse* response,
                     ::google::protobuf::Closure* done);

    // 添加好友
    void addFriend(::google::protobuf::RpcController* controller,
                   const ::ik_FriendService::AddFriendRequest* request,
                   ::google::protobuf::Empty* response,
                   ::google::protobuf::Closure* done);

    // 删除好友
    void deleteFriend(::google::protobuf::RpcController* controller,
                      const ::ik_FriendService::DeleteFriendRequest* request,
                      ::google::protobuf::Empty* response,
                      ::google::protobuf::Closure* done);

private:
    ik::LogServerRpc_Stub logStub_;
    ZKMaster master_;
};