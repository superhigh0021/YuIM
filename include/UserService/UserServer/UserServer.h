#pragma once

#include "LogServer.pb.h"
#include "UserServer.pb.h"

#include "ZookeeperFellow.h"

#include <sqlPool/connectPool.h>

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpccontroller.h>
#include <myrpc/myrpcchannel.h>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Timestamp.h>

#include <string>
#include <memory>
#include <functional>

class UserServer {
public:
    UserServer(const std::string& ip, uint16_t port);

    // 服务启动
    void run();

    // 读写事件回调
    void msgCallback(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp);

    // 连接事件回调函数
    void connCallback(const muduo::net::TcpConnectionPtr& conn);

public:
    // 登录
    bool Login(int id, const std::string& password);

    // 注销
    void LoginOut(int id);

    // 注册 成功返回注册的账户，失败返回-1
    int Register(const std::string& name, const std::string& password);

private:
    std::string ip_;
    uint16_t port_;

    ConnectPool* sqlPool_;
    muduo::net::EventLoop loop_;

    ik::LogServerRpc_Stub stub_;
};