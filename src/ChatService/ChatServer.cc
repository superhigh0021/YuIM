#include "ChatServer.h"

#include <iostream>

constexpr int BUFF_SIZE = 128;

// 开启服务
void ChatServer::run(std::string&& ip, uint16_t port) {
    // 初始化服务器信息
    muduo::net::InetAddress address(ip, port);
    muduo::net::TcpServer server(&loop_, address, "ChatServer");

    // 工作线程数
    server.setThreadNum(4);

    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
        onMessage(conn, buffer, stamp);
    });

    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        onConnect(conn);
    });

    // 连接redis服务器
    redisClient_.connect();

    // 注册到zookeeper节点
    zkClient_.start();
    std::string zkPath = "/ChatService/server";
    std::string zkData = ip + ":" + std::to_string(port);
    zkClient_.create(zkPath, zkPath.c_str(), strlen(zkPath.c_str()), ZOO_EPHEMERAL);

    // 开启muduo服务
    server.start();
    loop_.loop();
}

// 连接事件回调函数
void ChatServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buffer,
                           muduo::Timestamp stamp) {
    // 反序列化
    std::string recvStr = buffer->retrieveAllAsString();
    ik_ChatServer::MsgRequest request;
    request.ParseFromString(recvStr);

    // 得到用户登录的ip地址
    std::string host = redisClient_.getHost(request.id());
    // 如果当前用户没有登陆、写入离线消息
    if (host == "") {
        ik_OfflineService::WriteOfflineRequest writeRequest;
        writeRequest.set_friend_id(request.id());
        writeRequest.set_msg(request.msg());
        google::protobuf::Empty emp;
        MyrpcController controller;
        offlineStub_.WriteOffline(&controller, &writeRequest, &emp, nullptr);
        return;
    }

    // 如果map中没有这个连接conn，那么就创建
    if (auto it = channelMap_.find(host); it == channelMap_.end()) {
        int clientFd = establishConnection(host);
        channelMap_[host] = clientFd;
    }

    // 序列化
    ik_Proxy::ProxyMessage proxyRequest;
    proxyRequest.set_type("conveyMsg");
    proxyRequest.set_requestmsg(recvStr);

    std::string sendStr = proxyRequest.SerializeAsString();
    // 转发此消息
    auto channel = channelMap_.find(host);
    int fd = channel->second;
    if (::send(fd, sendStr.c_str(), strlen(sendStr.c_str()), 0) == -1) {
        // 打印错误日志
        ik::LogRequest logRequest;
        logRequest.set_name("ChatServer " + host);
        char errorBuffer[BUFF_SIZE] = {0};
        ::sprintf(errorBuffer, "send error ,errno:%d", errno);
        logRequest.set_msg(errorBuffer);
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &logRequest, &emp, nullptr);
    }
}

// 连接事件回调函数
void ChatServer::onConnect(const muduo::net::TcpConnectionPtr& conn) {
    // 关闭连接
    if (!conn->connected()) {
        conn->shutdown();
    }
}

// 根据host建立连接
int ChatServer::establishConnection(const std::string& host) {
    // 解析ip和host
    int index = host.find(":");
    std::string ip = host.substr(0, index);
    uint16_t port = atoi(host.substr(index + 1, host.size() - index).c_str());

    // 创建socket
    int clientFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (clientFd == -1) {
        // 打印错误日志
        ik::LogRequest request;
        request.set_name("ChatServer " + host);
        request.set_msg("create client fd error");
        google::protobuf::Empty em;
        stub_.Log_ERROR(nullptr, &request, &em, nullptr);

        ::close(clientFd);
        return -1;
    }

    // 配置服务器信息
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 连接
    if (::connect(clientFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        // 打印错误日志
        ik::LogRequest request;
        request.set_name("ChatServer " + host);
        request.set_msg("establish connect error");
        google::protobuf::Empty emp;
        stub_.Log_ERROR(nullptr, &request, &emp, nullptr);

        ::close(clientFd);
        return -1;
    }
    return clientFd;
}