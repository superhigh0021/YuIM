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

// 注册
void ProxyService::regist(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_UserService::RegisterRequest registRequest;
    registRequest.ParseFromString(recvBuf);

    // 执行
    ik_UserService::RegisterResponse response;
    userStub_.Registe(nullptr, &registRequest, &response, nullptr);

    // 序列化并发送
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// 注销业务
void ProxyService::loginOut(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_UserService::LoginOutRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    userStub_.LoginOut(nullptr, &request, nullptr, nullptr);
}

// 一对一聊天业务
void ProxyService::oneChat(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // todo
}

// 添加好友业务
void ProxyService::addFriend(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_FriendService::AddFriendRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    MyrpcController controller;
    google::protobuf::Empty emp;
    friendStub_.AddFriend(&controller, &request, &emp, nullptr);

    // 判断执行结果
    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// 删除好友
void ProxyService::deleteFriend(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_FriendService::DeleteFriendRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    MyrpcController controller;
    google::protobuf::Empty emp;
    friendStub_.DeleteFriend(&controller, &request, &emp, nullptr);

    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// 获取用户信息
void ProxyService::getUserInfo(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_FriendService::UserInfoRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    ik_FriendService::UserInfoResponse response;
    friendStub_.GetUserInfo(nullptr, &request, &response, nullptr);

    // 序列化并返回结果
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// 获取好友列表
void ProxyService::getFriendList(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_FriendService::FriendListRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    ik_FriendService::FriendListResponse response;
    friendStub_.GetFriendList(nullptr, &request, &response, nullptr);

    // 序列化并返回结果
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// 读取离线消息
void ProxyService::readOfflineMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_OfflineService::ReadOfflineRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    ik_OfflineService::ReadOfflineResponse response;
    offlineStub_.ReadOffline(nullptr, &request, &response, nullptr);

    // 序列化并返回结果
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// 创建群组
void ProxyService::createGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_GroupService::CreateGroupRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    MyrpcController controller;
    ik_GroupService::CreateGroupResponse response;
    groupStub_.CreateGroup(&controller, &request, &response, nullptr);
}

// 加入群组
void ProxyService::addGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_GroupService::AddGroupRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    MyrpcController controller;
    google::protobuf::Empty emp;
    groupStub_.AddGroup(&controller, &request, &emp, nullptr);

    // 判断执行结果
    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// 退出群
void ProxyService::quitGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_GroupService::QuitGroupRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    MyrpcController controller;
    google::protobuf::Empty emp;
    groupStub_.QuitGroup(&controller, &request, &emp, nullptr);

    // 判断执行结果
    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// 获得群用户信息
void ProxyService::getGroupUsers(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_GroupService::GetGroupUsersRequest request;
    request.ParseFromString(recvBuf);

    // 执行
    MyrpcController controller;
    ik_GroupService::GetGroupUsersResponse response;
    groupStub_.GetGroupUsers(&controller, &request, &response, nullptr);

    // 序列化
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// 转发而来的消息
void ProxyService::conveyMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_ChatServer::MsgRequest request;
    request.ParseFromString(recvBuf);

    ik_Proxy::ProxyResponse response;
    response.set_type("ChatMsg");
    response.set_responsemsg(request.msg());

    int id = request.id();

    {
        std::lock_guard lock(mutex_);
        auto it = userConnectionMap_.find(id);
        auto clientConn = it->second;
        clientConn->send(response.SerializeAsString());
    }
}

// 聊天消息
void ProxyService::chatMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // 反序列化
    ik_ChatServer::MsgRequest request;
    request.ParseFromString(recvBuf);

    int id = request.id();

    // 不在此台服务器上
    if (auto it = userConnectionMap_.find(id); it == userConnectionMap_.end()) {
        // 刷新服务器连接
        master_.getFollow();
        // 获取一个与转发服务器交互的可以连接
        int clientfd;
        while ((clientfd = master_.getService()) == -1) {
            master_.getFollow();
            sleep(1);
        }

        ::send(clientfd, recvBuf.c_str(), recvBuf.size(), 0);
    } else {
        it->second->send(recvBuf);
    }
}