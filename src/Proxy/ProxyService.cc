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

// ??????
void ProxyService::login(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_UserService::LoginRequest loginRequest;
    loginRequest.ParseFromString(recvBuf);

    // ??????
    ik_UserService::LoginResponse loginResponse;
    userStub_.Login(nullptr, &loginRequest, &loginResponse, nullptr);

    // ???redis??????????????????
    MyrpcConfig configure = MyrpcApplication::getInstance().getConfig();
    std::string ip = configure.Load("server_ip");
    uint16_t port = atoi(configure.Load("server_port").c_str());
    redisClient_.setHost(loginRequest.id(), ip + ":" + std::to_string(port));

    // ??????????????????usermap??????
    {
        std::lock_guard lock(mutex_);
        userConnectionMap_.emplace(loginRequest.id(), conn);
    }

    // ????????????????????????
    std::string sendStr = loginResponse.SerializeAsString();
    conn->send(sendStr);
}

// ??????
void ProxyService::regist(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_UserService::RegisterRequest registRequest;
    registRequest.ParseFromString(recvBuf);

    // ??????
    ik_UserService::RegisterResponse response;
    userStub_.Registe(nullptr, &registRequest, &response, nullptr);

    // ??????????????????
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// ????????????
void ProxyService::loginOut(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_UserService::LoginOutRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    userStub_.LoginOut(nullptr, &request, nullptr, nullptr);
}

// ?????????????????????
void ProxyService::oneChat(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // todo
}

// ??????????????????
void ProxyService::addFriend(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_FriendService::AddFriendRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    MyrpcController controller;
    google::protobuf::Empty emp;
    friendStub_.AddFriend(&controller, &request, &emp, nullptr);

    // ??????????????????
    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// ????????????
void ProxyService::deleteFriend(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_FriendService::DeleteFriendRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    MyrpcController controller;
    google::protobuf::Empty emp;
    friendStub_.DeleteFriend(&controller, &request, &emp, nullptr);

    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// ??????????????????
void ProxyService::getUserInfo(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_FriendService::UserInfoRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    ik_FriendService::UserInfoResponse response;
    friendStub_.GetUserInfo(nullptr, &request, &response, nullptr);

    // ????????????????????????
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// ??????????????????
void ProxyService::getFriendList(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_FriendService::FriendListRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    ik_FriendService::FriendListResponse response;
    friendStub_.GetFriendList(nullptr, &request, &response, nullptr);

    // ????????????????????????
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// ??????????????????
void ProxyService::readOfflineMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_OfflineService::ReadOfflineRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    ik_OfflineService::ReadOfflineResponse response;
    offlineStub_.ReadOffline(nullptr, &request, &response, nullptr);

    // ????????????????????????
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// ????????????
void ProxyService::createGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_GroupService::CreateGroupRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    MyrpcController controller;
    ik_GroupService::CreateGroupResponse response;
    groupStub_.CreateGroup(&controller, &request, &response, nullptr);
}

// ????????????
void ProxyService::addGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_GroupService::AddGroupRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    MyrpcController controller;
    google::protobuf::Empty emp;
    groupStub_.AddGroup(&controller, &request, &emp, nullptr);

    // ??????????????????
    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// ?????????
void ProxyService::quitGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_GroupService::QuitGroupRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    MyrpcController controller;
    google::protobuf::Empty emp;
    groupStub_.QuitGroup(&controller, &request, &emp, nullptr);

    // ??????????????????
    if (controller.Failed()) {
        conn->send(controller.ErrorText());
    }
}

// ?????????????????????
void ProxyService::getGroupUsers(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_GroupService::GetGroupUsersRequest request;
    request.ParseFromString(recvBuf);

    // ??????
    MyrpcController controller;
    ik_GroupService::GetGroupUsersResponse response;
    groupStub_.GetGroupUsers(&controller, &request, &response, nullptr);

    // ?????????
    std::string sendStr = response.SerializeAsString();
    conn->send(sendStr);
}

// ?????????????????????
void ProxyService::conveyMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
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

// ????????????
void ProxyService::chatMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {
    // ????????????
    ik_ChatServer::MsgRequest request;
    request.ParseFromString(recvBuf);

    int id = request.id();

    // ????????????????????????
    if (auto it = userConnectionMap_.find(id); it == userConnectionMap_.end()) {
        // ?????????????????????
        master_.getFollow();
        // ???????????????????????????????????????????????????
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

// ??????????????????????????????
MsgHandler ProxyService::getHandler(std::string msgType) {
    // ?????????????????????msgid?????????????????????????????????
    if (auto it = msgHandlerMap_.find(msgType); it == msgHandlerMap_.end()) {
        // ???????????????????????????
        ik::LogRequest request;
        request.set_name("ProxyService");
        request.set_msg("have this service" + msgType);
        google::protobuf::Empty emp;
        logStub_.Log_ERROR(nullptr, &request, &emp, nullptr);

        return [](const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time) {};
    } else {
        return msgHandlerMap_[msgType];
    }
}

// ???????????????????????????
void ProxyService::clientCloseException(const muduo::net::TcpConnectionPtr& conn) {
    // ??????usermap->????????????offline->????????????->??????redis????????????
    std::lock_guard lock(mutex_);
    for (auto it = userConnectionMap_.begin(); it != userConnectionMap_.end(); ++it) {
        if (it->second == conn) {
            redisClient_.delHost(it->first);
            it = userConnectionMap_.erase(it);
            break;
        }
    }
}

// ??????????????????????????????
void ProxyService::reset() {
    // ?????????????????????????????????
    ik_Proxy::ProxyResponse response;
    response.set_type("LoginOut");
    response.set_responsemsg("server crash");
    std::string sendStr = response.SerializeAsString();

    {
        std::lock_guard lock(mutex_);
        // ???????????????????????????
        ik_UserService::LoginOutRequest request;
        for (auto it = userConnectionMap_.begin(); it != userConnectionMap_.end(); ++it) {
            request.set_id(it->first);

            // ???redis???????????????
            redisClient_.delHost(it->first);

            google::protobuf::Empty emp;
            userStub_.LoginOut(nullptr, &request, &emp, nullptr);

            it->second->send(sendStr);
        }
    }

    // ??????map
    std::unordered_map<int, muduo::net::TcpConnectionPtr>().swap(userConnectionMap_);
}