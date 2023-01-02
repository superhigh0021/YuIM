#include "ProxyServer.h"

#include <future>

// 初始化服务器信息
ProxyServer::ProxyServer(muduo::net::EventLoop& loop,
                         muduo::net::InetAddress& address,
                         const std::string& name) :
    loop_(loop),
    server_(&loop, address, name) {
    // 注册连接事件回调函数
    server_.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        onConnect(conn);
    });

    // 注册消息事件回调函数
    server_.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
        onMessage(conn, buffer, stamp);
    });

    // 设置工作线程数量
    // 最佳线程数目 = (线程等待时间与线程CPU时间之比 + 1) * CPU数目  =>高网络IO设计
    server_.setThreadNum(4);
}

// 代理服务器开始工作
void ProxyServer::start() {
    server_.start();
}

// 连接事件的回调函数
void ProxyServer::onConnect(const muduo::net::TcpConnectionPtr& conn) {
    // TODO...
}

// 读写事件回调函数
void ProxyServer::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
    // TODO...
}
