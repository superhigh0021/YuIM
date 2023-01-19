#include "FriendService.pb.h"

#include <myrpc/myrpcchannel.h>
#include <myrpc/myrpcapplication.h>

#include <google/protobuf/service.h>
#include <google/protobuf/empty.pb.h>

#include <iostream>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().Init(argc, argv);
    ik_FriendService::FriendServiceRpc_Stub stub(new MyrpcChannel);
    ik_FriendService::AddFriendRequest request;
    request.set_myid(1);
    request.set_friendid(4);

    ik_FriendService::FriendListResponse response;
    google::protobuf::Empty emp;
    stub.AddFriend(nullptr, &request, &emp, nullptr);

    return 0;
}