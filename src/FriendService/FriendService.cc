#include "FriendService.h"

#include <chrono>

constexpr int BUFF_SIZE = 256;

FriendService::FriendService() :
    logStub_(new MyrpcChannel), master_("/FriendService") {
    master_.start();
}

// 获取好友列表
void FriendService::getFriendList(::google::protobuf::RpcController* controller,
                                  const ::ik_FriendService::FriendListRequest* request,
                                  ::ik_FriendService::FriendListResponse* response,
                                  ::google::protobuf::Closure* done) {
    // 刷新zookeeper列表
    master_.getFollow();
    // 反序列化
    ik_FriendServer::Request getRequest;
    getRequest.set_type("getFriendList");
    getRequest.set_request(request->SerializeAsString());

    // 获得一个可用的连接
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 发送任务信息
    std::string sendStr = getRequest.SerializeAsString();
    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 打印日志
        ik::LogRequest logRequest;
        logRequest.set_name("FriendService");
        logRequest.set_msg("send error");
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);

        response->set_is_success(false);
        done->Run();
        return;
    }

    // 获取返回信息
    char recvBuf[BUFF_SIZE] = {0};
    if (::recv(clientFd, recvBuf, BUFF_SIZE, 0) == -1) {
        // 打印日志
        ik::LogRequest logRequest;
        logRequest.set_name("FriendService");
        logRequest.set_msg("recv error");
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);

        response->set_is_success(false);
        done->Run();
        return;
    }

    response->ParseFromString(recvBuf);
    ::close(clientFd);
    done->Run();
}

// 获取用户信息
void FriendService::getUserInfo(::google::protobuf::RpcController* controller,
                                const ::ik_FriendService::UserInfoRequest* request,
                                ::ik_FriendService::UserInfoResponse* response,
                                ::google::protobuf::Closure* done) {
    // 刷新zookeeper列表
    master_.getFollow();
    // 反序列化
    ik_FriendServer::Request getRequest;
    getRequest.set_type("getUserInfo");
    getRequest.set_request(request->SerializeAsString());

    // 获取一个可用的连接
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 发送任务信息
    std::string sendStr = getRequest.SerializeAsString();
    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 打印日志
        ik::LogRequest logRequest;
        logRequest.set_name("FriendService");
        logRequest.set_msg("send error");
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);

        controller->SetFailed("send error");
        done->Run();
        return;
    }

    // 获取返回信息
    char recvBuf[BUFF_SIZE] = {0};
    if (::recv(clientFd, recvBuf, BUFF_SIZE, 0) == -1) {
        // 打印日志
        ik::LogRequest logRequest;
        logRequest.set_name("FriendService");
        logRequest.set_msg("recv error");
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);

        controller->SetFailed("recv error");
        done->Run();
        return;
    }

    response->ParseFromString(recvBuf);
    ::close(clientFd);
    done->Run();
}

// 添加好友
void FriendService::addFriend(::google::protobuf::RpcController* controller,
                              const ::ik_FriendService::AddFriendRequest* request,
                              ::google::protobuf::Empty* response,
                              ::google::protobuf::Closure* done) {
    // 刷新zookeeper列表
    master_.getFollow();
    // 反序列化
    ik_FriendServer::Request getRequest;
    getRequest.set_type("addFriend");
    getRequest.set_request(request->SerializeAsString());

    // 获取一个可用的连接
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 发送任务信息
    std::string sendStr = getRequest.SerializeAsString();
    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 打印日志
        ik::LogRequest logRequest;
        logRequest.set_name("FriendService");
        logRequest.set_msg("send error");
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);

        controller->SetFailed("send error");
        done->Run();
        return;
    }

    ::close(clientFd);
    done->Run();
}

void FriendService::deleteFriend(::google::protobuf::RpcController* controller,
                                 const ::ik_FriendService::DeleteFriendRequest* request,
                                 ::google::protobuf::Empty* response,
                                 ::google::protobuf::Closure* done) {
    // 刷新zookeeper列表
    master_.getFollow();
    // 反序列化
    ik_FriendServer::Request getRequest;
    getRequest.set_type("deleteFriend");
    getRequest.set_request(request->SerializeAsString());

    // 获取一个可用的连接
    int clientFd;
    while ((clientFd = master_.getService()) == -1) {
        master_.getFollow();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 发送任务信息
    std::string sendStr = getRequest.SerializeAsString();
    if (::send(clientFd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 打印日志
        ik::LogRequest logRequest;
        logRequest.set_name("FriendService");
        logRequest.set_msg("send error");
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);

        controller->SetFailed("send error");
        done->Run();
        return;
    }

    ::close(clientFd);
    done->Run();
}