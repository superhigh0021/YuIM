#include "LogSend.h"
#include "LogSend.pb.h"

#include <functional>
#include <cstdlib>
#include <cstring>
#include <iostream>

constexpr int  SEND_SIZE = 256;

// 开始服务
void LogSend::run(std::string ip, uint16_t port) {
    muduo::net::InetAddress address(ip, port);
    muduo::net::TcpServer server(&loop_, address, "LogSend");

    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp stamp) {
        sendFile(conn, buf, stamp);
    });
    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        closeConn(conn);
    });
    server.setThreadNum(2);

    server.start();
    loop_.loop();
}

// 读取文件并发送消息，绑定到muduo的on_message消息回调
void LogSend::sendFile(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp stamp) {
    std::string recv = buf->retrieveAllAsString().c_str();
    ik::LogSendRequest request;
    request.ParseFromString(recv);

    std::string filePath = "../log/";
    filePath += request.node_name();
    filePath += "/";
    filePath += request.time() + "_log.txt";
    std::cout << "filePath is:" << filePath << "\n";

    ik::LogSendResponse response;
    int count = 1;
    char sendBuf[SEND_SIZE] = {0};
    FILE* fp = fopen(filePath.c_str(), "r");
    while (!feof(fp)) {
        bzero(sendBuf, SEND_SIZE);
        fgets(sendBuf, SEND_SIZE, fp);
        response.set_serial(count++);
        response.set_is_end(false);
        response.set_msg(sendBuf);

        std::string sendStr;
        response.SerializePartialToString(&sendStr);
        conn->send(sendStr.c_str(), strlen(sendStr.c_str()));
    }

    response.set_serial(count++);
    response.set_is_end(true);

    std::string sendStr;
    response.SerializePartialToString(&sendStr);
    conn->send(sendStr.c_str(), strlen(sendStr.c_str()));
}

// 关闭连接
void LogSend::closeConn(const muduo::net::TcpConnectionPtr& conn) {
    if (!conn->connected()) {
        // 与rpc client断开连接
        conn->shutdown();
    }
}