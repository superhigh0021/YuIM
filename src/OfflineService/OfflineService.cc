#include "OfflineService.h"

constexpr int BUFF_SIZE = 128;

OfflineService::OfflineService() :
    stub_(new MyrpcChannel), master_("/OfflineService") {
    master_.start();
}

void OfflineService::WriteOffline(::google::protobuf::RpcController* controller,
                                  const ::ik_OfflineService::WriteOfflineRequest* request,
                                  ::google::protobuf::Empty* response,
                                  ::google::protobuf::Closure* done) {
    // 刷新服务列表
    master_.getFollow();
    ik_OfflineServer::Request sendRequest;

    // 重新序列化
    sendRequest.set_type("WriteOffline");
    sendRequest.set_requestmsg(request->SerializeAsString());

    std::string sendStr = sendRequest.SerializeAsString();
    int clientFd = master_.getService();
    while (clientFd == -1) {
        master_.getFollow();
        sleep(1);
    }

    if (::send(clientFd, sendStr.c_str(), sendStr.size(), 0) == -1) {
        // 如果发生失败
        controller->SetFailed("write offline command send error");
        // 打印错误信息
        ik::LogRequest logRequest;
        logRequest.set_name("OfflineService");
        logRequest.set_msg("write offline command send error");
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);
    }
}

void OfflineService::ReadOffline(::google::protobuf::RpcController* controller,
                                 const ::ik_OfflineService::ReadOfflineRequest* request,
                                 ::ik_OfflineService::ReadOfflineResponse* response,
                                 ::google::protobuf::Closure* done) {
    // 刷新服务列表
    master_.getFollow();
    ik_OfflineServer::Request sendRequest;

    // 重新序列化
    sendRequest.set_type("GetGroupUsers");
    sendRequest.set_requestmsg(request->SerializeAsString());

    std::string sendStr = sendRequest.SerializeAsString();
    int clientFd = master_.getService();
    while (clientFd == -1) {
        master_.getFollow();
        sleep(1);
    }

    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0)) {
        // 如果发生失败
        controller->SetFailed("get offline msg command send error");
        // 打印错误消息
        ik::LogRequest logRequest;
        logRequest.set_name("OfflineService");
        logRequest.set_msg("get offline msg command send error");
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);
    }
}