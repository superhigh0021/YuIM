#include "GroupServer.h"

constexpr int BUFF_SIZE = 128;

// 初始化server信息
GroupServer::GroupServer(std::string&& ip, uint16_t port) :
    ip_(ip), port_(port), pool_(ConnectPool::getInst()) {
}

// 开始运行服务
void GroupServer::run() {
    // 初始化服务器底层网络信息
    muduo::net::InetAddress address(ip_, port_);
    muduo::net::TcpServer server(&loop_, address, "GroupServer");

    // 工作线程数
    server.setThreadNum(4);

    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
        onMessage(conn, buffer, stamp);
    });

    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        onConnect(conn);
    });

    zkClient_.start();
    std::string serverPath = "/GroupService/server";
    std::string host = ip_ + ":" + std::to_string(port_);
    zkClient_.create(serverPath, host.c_str(), strlen(host.c_str()), ZOO_EPHEMERAL);

    server.start();
    loop_.loop();
}

// 绑定连接事件
void GroupServer::onConnect(const muduo::net::TcpConnectionPtr& conn) {
    // 简单断开连接
    if (!conn->connected()) {
        conn->shutdown();
    }
}

// 绑定连接读写事件
void GroupServer::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
    // 反序列化
    std::string recvStr = buffer->retrieveAllAsString();
    ik_GroupServer::Request request;
    request.ParseFromString(recvStr);

    // 判断业务逻辑
    if (request.type() == "addGroup") {
        ik_GroupServer::AddGroupRequest addRequest;
        addRequest.ParseFromString(request.request_msg());
        int userid = addRequest.userid();
        int groupid = addRequest.groupid();

        addGroup(userid, groupid);
    } else if (request.type() == "quitGroup") {
        ik_GroupServer::QuitGroupRequest quitRequest;
        quitRequest.ParseFromString(request.request_msg());
        int userid = quitRequest.userid();
        int groupid = quitRequest.groupid();

        quitGroup(userid, groupid);
    } else if (request.type() == "createGroup") {
        ik_GroupServer::CreateGroupRequest createRequest;
        createRequest.ParseFromString(request.request_msg());
        int userid = createRequest.userid();
        std::string groupName = createRequest.groupname();

        int groupid = createGroup(userid, std::move(groupName));
        if (groupid != -1) {
            addGroup(userid, groupid);
            ik_GroupServer::CreateGroupResponse response;
            response.set_groupid(groupid);
            conn->send(response.SerializeAsString());
        }
    } else if (request.type() == "GetGroupUsers") {
        ik_GroupServer::GetGroupUsersRequest getRequest;
        getRequest.ParseFromString(request.request_msg());

        int groupid = getRequest.groupid();
        auto users = getGroupUsers(groupid);
        ik_GroupServer::GetGroupUsersResponse getResponse;
        ik_GroupServer::UserInfo* userInfo = nullptr;

        for (auto user : users) {
            // 注意这里是指针，所以可以操作response里的内容，添加所有成员后返回回去
            userInfo = getResponse.add_users();
            userInfo->set_id(user.getId());
            userInfo->set_name(user.getName());
        }
        conn->send(getResponse.SerializeAsString());
    }
}

// 将userid所代表的用户添加到groupid的群里
bool GroupServer::addGroup(int userid, int groupid) {
    // 从连接池中取出一条连接
    auto conn = pool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "insert into GroupUser values(%d, %d)", userid, groupid);
    return conn->update(sql);
}

// 创建群、群名为groupName、返回群号
int GroupServer::createGroup(int userid, std::string&& groupName) {
    auto conn = pool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "insert into AllGroup(groupname) values('%s')", groupName.c_str());
    conn->update(sql);

    return mysql_insert_id(conn->getConnection());
}

// 在groupid的群里删除userid这一列
bool GroupServer::quitGroup(int userid, int groupid) {
    auto conn = pool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "delete from GroupUSer where userid = %d and groupid = %d", userid, groupid);
    return conn->update(sql);
}

// 得到群组中所有用户信息
std::vector<User> GroupServer::getGroupUsers(int groupid) {
    auto conn = pool_->getConnect();
    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "select User.id, User.name from User, GroupUser where GroupUser.groupid = %d and GroupUser.userid = User.id", groupid);
    auto res = conn->query(sql);
    MYSQL_ROW row;

    std::vector<User> users;
    while ((row = mysql_fetch_row(res))) {
        User user;
        user.setId(atoi(row[0]));
        user.setName(row[1]);
        users.emplace_back(user);
    }

    mysql_free_result(res);
    return users;
}