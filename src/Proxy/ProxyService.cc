#include "ProxyService.h"

ProxyService::ProxyService() :
    master_("/ChatService"),
    groupStub_(new MyrpcChannel),
    userStub_(new MyrpcChannel),
    friendStub_(new MyrpcChannel),
    offlineStub_(new MyrpcChannel),
    logStub_(new MyrpcChannel) {
    msgHandlerMap_.emplace("Login", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        login(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("Regist", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        login(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("LoginOut", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        regist(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("oneChat", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        oneChat(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("AddFriend", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        addFriend(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("DeleteFriend", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        deleteFriend(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("GetUserInfo", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        getUserInfo(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("GetFriendList", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        getFriendList(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("ReadOfflineMsg", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        readOfflineMsg(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("CreateGroup", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        createGroup(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("AddGroup", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        addGroup(conn, recvBuf, time);
    });
    msgHandlerMap_.emplace("QuitGroup", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        quitGroup(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("GetGroupUsers", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        getGroupUsers(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("ChatMsg", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        chatMsg(conn, recvBuf, time);
    });

    msgHandlerMap_.emplace("ConveyMsg", [this](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
        conveyMsg(conn, recvBuf, time);
    });

    master_.start();
}

// 登录
void ProxyService::login(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_UserService::LoginRequest loginRequest;
    loginRequest.ParseFromString(recvBuf);

    // 执行
    ik_UserService::LoginResponse loginResponse;
    userStub_.Login(nullptr, &loginRequest, &loginResponse, nullptr);

    // 在redis上记录此用户
    MyrpcConfig configure = MyrpcApplication::getInstance().getConfig();
    std::string ip = configure.Load("server_ip");
    uint16_t port = atoi(configure.Load("server_port").c_str());
    redisClient_.setHost(loginRequest.id(), ip + ":" + std::to_string(port));

    // 添加此用户到usermap表中
    {
        std::lock_guard lock(mutex_);
        userConnectionMap_.emplace(loginRequest.id(), conn);
    }

    // 序列化消息并发送
    std::string sendStr = loginResponse.SerializeAsString();
    conn->send(sendStr);
}