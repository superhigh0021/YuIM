#include "UserService.h"

#include <iostream>
#include <memory>

constexpr int BUFF_SIZE = 256;

UserService::UserService() :
    stub_(new MyrpcChannel), master_("/UserService") {
    master_.start();
}

void UserService::Login(::google::protobuf::RpcController* controller,
                        const ::ik_UserService::LoginRequest* request,
                        ::ik_UserService::LoginResponse* response,
                        ::google::protobuf::Closure* done) {
    master_.getFollow();
    ik_UserServer::Request loginRequest;
    loginRequest.set_type("Login");
    loginRequest.set_request(request->SerializeAsString());

    std::string sendStr = loginRequest.SerializeAsString();
    // 获取一个服务信息
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        // 刷新服务列表
        master_.getFollow();
        sleep(1);
    }

    // 发送消息
    ::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0);

    // 获取信息
    char recvBuf[BUFF_SIZE] = {0};
    ::recv(clientFd, recvBuf, BUFF_SIZE, 0);
    ik_UserServer::LoginResponse loginResponse;

    loginResponse.ParseFromString(recvBuf);
    response->set_is_success(loginResponse.is_success());

    ::close(clientFd);
    done->Run();
}

void UserService::Registe(::google::protobuf::RpcController* controller,
                          const ::ik_UserService::RegisterRequest* request,
                          ::ik_UserService::RegisterResponse* response,
                          ::google::protobuf::Closure* done) {
    master_.getFollow();
    ik_UserServer::Request registerRequest;
    registerRequest.set_type("Resgister");
    registerRequest.set_request(request->SerializeAsString());

    std::string sendStr = registerRequest.SerializeAsString();
    // 获取一个服务信息
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        // 刷新服务列表
        master_.getFollow();
        sleep(1);
    }

    // 发送信息
    ::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0);

    // 获取信息
    char recvBuf[BUFF_SIZE] = {0};
    recv(clientFd, recvBuf, BUFF_SIZE, 0);
    ik_UserServer::RegisterResponse registerResponse;

    registerResponse.ParseFromString(recvBuf);
    response->set_id(registerResponse.id());
    response->set_is_success(registerResponse.is_success());

    close(clientFd);
    done->Run();
}

void UserService::LoginOut(::google::protobuf::RpcController* controller,
                           const ::ik_UserService::LoginOutRequest* request,
                           ::google::protobuf::Empty* response,
                           ::google::protobuf::Closure* done) {
    master_.getFollow();
    ik_UserServer::Request loginoutRequest;
    loginoutRequest.set_type("LoginOut");
    loginoutRequest.set_request(request->SerializeAsString());

    std::string sendStr = loginoutRequest.SerializeAsString();
    // 获取一个服务信息
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        // 刷新服务列表
        master_.getFollow();
        sleep(1);
    }

    // 发送信息
    ::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0);

    ::close(clientFd);
    done->Run();
}