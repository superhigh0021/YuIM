#include "FriendServer.h"

constexpr int BUFF_SIZE = 128;

FriendServer::FriendServer(std::string&& ip, uint16_t port) :
    ip_(ip), port_(port), sqlPool_(ConnectPool::getInst()) {
}

// 服务器运行
void FriendServer::run() {
    muduo::net::InetAddress address(ip_, port_);
    muduo::net::TcpServer server(&loop_, address, "FriendServer");

    // 注册到zookeeper节点
    ZKClient client;
    client.start();
    std::string serverPath = "/FriendService/server";
    char data[BUFF_SIZE] = {0};
    ::sprintf(data, "%s:%u", ip_.c_str(), port_);
    client.create(serverPath, data, strlen(data), ZOO_EPHEMERAL);

    // 工作线程数
    server.setThreadNum(4);

    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
        onMessage(conn, buffer, stamp);
    });

    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        onConnect(conn);
    });

    server.start();
    loop_.loop();
}

// 读写事件回调
void FriendServer::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
    std::string recv = buffer->retrieveAllAsString();
    ik_FriendServer::Request request;
    request.ParseFromString(recv);

    if (request.type() == "getFriendList") {
        // 反序列化
        ik_FriendServer::FriendListsRequest friendlistRequest;
        friendlistRequest.ParseFromString(request.request());
        int userid = friendlistRequest.id();
        // 获取好友列表
        auto users = getFriendlist(userid);
        ik_FriendServer::FriendListResponse response;
        response.set_is_success(true);

        for (const auto& user : users) {
            auto info = response.add_friends();
            info->set_id(user.getId());
            info->set_name(user.getName());
        }

        std::string sendStr = response.SerializeAsString();
        conn->send(sendStr);
    } else if (request.type() == "getUserInfo") {
        // 反序列化
        ik_FriendServer::UserInfoRequest userRequest;
        userRequest.ParseFromString(request.request());

        // 序列化
        User user = getUserInfo(userRequest.id());
        ik_FriendServer::FriendInfo info;
        info.set_id(user.getId());
        info.set_name(user.getName());

        // 信息发送
        std::string sendStr = info.SerializeAsString();
        conn->send(sendStr);
    } else if (request.type() == "addFriend") {
        // 反序列化
        ik_FriendServer::AddFriendRequest addRequest;
        addRequest.ParseFromString(request.request());

        addFriend(addRequest.myid(), addRequest.friendid());
    } else if (request.type() == "deleteFriend") {
        // 反序列化
        ik_FriendServer::DeleteFriendRequest delRequest;
        delRequest.ParseFromString(request.request());

        deleteFriend(delRequest.myid(), delRequest.friendid());
    }
}

// 连接事件的回调函数
void FriendServer::onConnect(const muduo::net::TcpConnectionPtr& conn) {
    // 断开连接
    if (!conn->connected()) {
        conn->shutdown();
    }
}

// 获取userid用户的好友列表
std::vector<User> FriendServer::getFriendlist(int userid) {
    auto conn = sqlPool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "select User.id, User.name from Friend, User where Friend.userid = %d and User.id = Friend.friendid", userid);
    auto res = conn->query(sql);
    MYSQL_ROW row;

    std::vector<User> users;
    while ((row = mysql_fetch_row(res))) {
        User user;
        user.setId(atoi(row[0]));
        user.setName(std::string(row[0]));
        users.emplace_back(user);
    }
    mysql_free_result(res);
    return users;
}

// 获取userid用户信息
User FriendServer::getUserInfo(int userid) {
    auto conn = sqlPool_->getConnect();
    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "select name from User where id = %d", userid);
    auto res = conn->query(sql);
    if (res == nullptr) {
        // 没有的话返回 id = -1
        User user;
        user.setId(-1);
        return user;
    }
    User user;
    auto row = mysql_fetch_row(res);
    user.setId(userid);
    user.setName(std::string(row[0]));

    mysql_free_result(res);
    return user;
}

// userid的用户添加好友friendid
void FriendServer::addFriend(int userid, int friendid) {
    auto conn = sqlPool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "insert into Friend values(%d, %d)", userid, friendid);

    conn->update(sql);
}

// 删除userid用户的好友 friendid
void FriendServer::deleteFriend(int userid, int friendid) {
    auto conn = sqlPool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    sprintf(sql, "delete from Friend where userid=%d and friendid=%d", userid, friendid);

    conn->update(sql);
}