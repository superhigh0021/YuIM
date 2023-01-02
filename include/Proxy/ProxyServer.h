#pragma once

#include <muduo/net/Buffer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "ProxyService.h"
#include "ProxyServer.pb.h"

#include <string>
#include <functional>

class ProxyServer {
public:
    // 初始化服务器信息
    ProxyServer(muduo::net::EventLoop& loop, muduo::net::InetAddress& address, const std::string& name);

    // 代理服务器开始工作
    void start();

    // 连接事件回调函数
    void onConnect(const muduo::net::TcpConnectionPtr& conn);

    // 读写事件回调函数
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp);

private:
    muduo::net::TcpServer server_; // server对象

    muduo::net::EventLoop& loop_; // main loop
};