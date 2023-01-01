#pragma once
#include "LogSend.pb.h"

#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/Buffer.h>

#include <string>

class LogSend {
public:
    // 开始服务
    void run(std::string ip, uint16_t port);

    // 读取文件并发送消息，绑定到muduo的on_message消息回调
    void sendFile(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp stamp);

    // 关闭连接
    void closeConn(const muduo::net::TcpConnectionPtr& conn);

private:
    muduo::net::EventLoop loop_;
};