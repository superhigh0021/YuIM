#include "GroupService.h"

constexpr int BUFF_SIZE = 128;

GroupService::GroupService() :
    stub_(new MyrpcChannel),
    master_("/GroupService") {
    master_.start();
}

void GroupService::addGroup(::google::protobuf::RpcController* controller,
                            const ::ik_GroupService::AddGroupRequest* request,
                            ::google::protobuf::Empty* response,
                            ::google::protobuf::Closure* done) {
    // 刷新服务列表
    master_.getFollow();
    ik_GroupServer::Request sendRequest;

    // 重新序列化
    sendRequest.set_type("addGroup");
    sendRequest.set_request_msg(request->SerializeAsString());

    std::string sendStr = sendRequest.SerializeAsString();
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        sleep(1);
    }

    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 如果发生失败
        controller->SetFailed("addgroup command send error");
        // 打印错误信息
        ik::LogRequest log_request;
        log_request.set_name("GroupService");
        log_request.set_msg("addgroup command send error");
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &log_request, &emp, nullptr);
    }
}

void GroupService::createGroup(::google::protobuf::RpcController* controller,
                               const ::ik_GroupService::CreateGroupRequest* request,
                               ::ik_GroupService::CreateGroupResponse* response,
                               ::google::protobuf::Closure* done) {
    // 刷新服务列表
    master_.getFollow();
    ik_GroupServer::Request sendRequest;

    // 重新序列化
    sendRequest.set_type("createGroup");
    sendRequest.set_request_msg(request->SerializeAsString());

    std::string sendStr = sendRequest.SerializeAsString();
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        sleep(1);
    }

    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 如果发生失败
        controller->SetFailed("addgroup command send error");
        // 打印错误信息
        ik::LogRequest log_request;
        log_request.set_name("GroupService");
        log_request.set_msg("addgroup command send error");
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &log_request, &emp, nullptr);
    }

    char recvBuf[BUFF_SIZE] = {0};
    if (::recv(clientFd, recvBuf, BUFF_SIZE, 0) == -1) {
        // 如果发生失败
        controller->SetFailed("creategroup command recv error");
        // 打印错误信息
        ik::LogRequest logRequest;
        logRequest.set_name("GroupService");
        logRequest.set_msg("creategroup command recv error");
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);
    }

    response->ParseFromString(recvBuf);
}

void GroupService::quitGroup(::google::protobuf::RpcController* controller,
                             const ::ik_GroupService::QuitGroupRequest* request,
                             ::google::protobuf::Empty* response,
                             ::google::protobuf::Closure* done) {
    // 刷新服务列表
    master_.getFollow();
    ik_GroupServer::Request sendRequest;

    // 重新序列化
    sendRequest.set_type("quitGroup");
    sendRequest.set_request_msg(request->SerializeAsString());

    string sendStr = sendRequest.SerializeAsString();
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        sleep(1);
    }

    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 如果发生失败
        controller->SetFailed("quitgroup command send error");
        // 打印错误信息
        ik::LogRequest logRequest;
        logRequest.set_name("GroupService");
        logRequest.set_msg("quitgroup command send error");
        google::protobuf::Empty em;
        stub_.Log_ERROR(nullptr, &logRequest, &em, nullptr);
    }
}

void GroupService::getGroupUsers(::google::protobuf::RpcController* controller,
                                 const ::ik_GroupService::GetGroupUsersRequest* request,
                                 ::ik_GroupService::GetGroupUsersResponse* response,
                                 ::google::protobuf::Closure* done) {
    // 刷新服务列表
    master_.getFollow();
    ik_GroupServer::Request send_request;

    // 重新序列化
    send_request.set_type("getGroupUsers");
    send_request.set_request_msg(request->SerializeAsString());

    string sendStr = send_request.SerializeAsString();
    int clientFd = master_.getService();
    while (clientFd == -1) {
        master_.getFollow();
        sleep(1);
    }

    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 如果发生失败
        controller->SetFailed("get group users command send error");
        // 打印错误信息
        ik::LogRequest logRequest;
        logRequest.set_name("GroupService");
        logRequest.set_msg("get group users command send error");
        google::protobuf::Empty em;
        stub_.Log_ERROR(nullptr, &logRequest, &em, nullptr);
    }

    char recvBuf[BUFF_SIZE] = {0};
    if (recv(clientFd, recvBuf, BUFF_SIZE, 0) == -1) {
        // 如果发生失败
        controller->SetFailed("get group users command recv error");
        // 打印错误信息
        ik::LogRequest logRequest;
        logRequest.set_name("GroupService");
        logRequest.set_msg("get group users command recv error");
        google::protobuf::Empty em;
        stub_.Log_ERROR(nullptr, &logRequest, &em, nullptr);
    }

    response->ParseFromString(recvBuf);
}