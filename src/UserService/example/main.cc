#include "UserService.pb.h"

#include <myrpc/myrpcchannel.h>
#include <myrpc/myrpcapplication.h>

#include <google/protobuf/service.h>
#include <google/protobuf/empty.pb.h>

#include <iostream>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().Init(argc, argv);
    ik_UserService::UserServiceRpc_Stub stub(new MyrpcChannel);
    ik_UserService::LoginRequest request;
    request.set_id(1);
    request.set_password("123456");

    ik_UserService::LoginResponse response;
    stub.Login(nullptr, &request, &response, nullptr);
}