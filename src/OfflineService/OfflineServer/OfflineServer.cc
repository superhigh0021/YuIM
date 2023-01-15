#include "OfflineServer.h"

constexpr int BUFF_SIZE = 128;

// 初始化配置等信息
OfflineServer::OfflineServer(std::string&& ip, uint16_t port) :
    ip_(std::move(ip)),
    port_(port),
    pool_(ConnectPool::getInst()) {
}

// 开始服务
void OfflineServer::run() {
    muduo::net::InetAddress address(ip_, port_);
    muduo::net::TcpServer server(&loop_, address, "OfflineServer");

    // 注册zookeeper节点
    ZKClient client;
    client.start();
    std::string serverPath = "/OfflineService/server";
    char data[BUFF_SIZE] = {0};
    ::sprintf(data, "%s:%d", ip_.c_str(), port_);
    client.create(serverPath, data, strlen(data), ZOO_EPHEMERAL);

    // 绑定回调函数
    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
        onMessage(conn, buffer, stamp);
    });

    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        on_connect(conn);
    });

    server.setThreadNum(4);
    server.start();
    loop_.loop();
}

// 读写事件回调
void OfflineServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                              muduo::net::Buffer* buffer,
                              muduo::Timestamp stamp) {
    std::string recv = buffer->retrieveAllAsString();
    ik_OfflineServer::Request request;
    request.ParseFromString(recv);

    if (request.type() == "WriteOffline") {
        // 反序列化
        ik_OfflineServer::WriteOfflineRequest writeRequest;
        writeRequest.ParseFromString(request.requestmsg());
        int friendId = writeRequest.friend_id();
        std::string msg = writeRequest.msg();

        // 写入数据库
        writeOfflineMsg(friendId, std::move(msg));
    } else if (request.type() == "ReadOffline") {
        // 反序列化
        ik_OfflineServer::WriteOfflineRequest writeRequest;
        writeRequest.ParseFromString(request.requestmsg());
        int userId = writeRequest.friend_id();

        // 执行业务
        auto offlineMsg = readOfflineMsg(userId);

        // 反序列化
        ik_OfflineServer::ReadOfflineResponse response{};
        for (const auto& msg : offlineMsg) {
            response.add_msg(msg);
        }

        // 信息发送
        std::string sendStr = response.SerializeAsString();
        conn->send(sendStr);
    }
}

// 连接事件回调函数
void OfflineServer::on_connect(const muduo::net::TcpConnectionPtr& conn) {
    // 断开连接
    if (!conn->connected()) {
        conn->shutdown();
    }
}

// 写离线消息
bool OfflineServer::writeOfflineMsg(int friendId, std::string&& msg) {
    // 获取连接池连接
    auto conn = pool_->getConnect();

    // 组织sql语句并执行
    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "insert into Offline Message values(%d, '%s')", friendId, msg.c_str());
    return conn->update(sql);
}

// 读离线消息
std::vector<std::string> OfflineServer::readOfflineMsg(int myid) {
    // 获取数据库连接池
    auto conn = pool_->getConnect();

    // 组织sql语句并执行
    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "select message from OfflineMessage where userid = %d", myid);
    auto res = conn->query(sql);
    MYSQL_ROW row;
    std::vector<std::string> ret;
    while ((row = mysql_fetch_row(res))) {
        ret.emplace_back(row[0]);
    }

    mysql_free_result(res);

    // 删除原来的离线消息
    bzero(sql, BUFF_SIZE);
    ::sprintf(sql, "delete from OfflineMessage where userid = %d", myid);

    conn->update(sql);
    return ret;
}