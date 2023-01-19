#pragma once

#include "ZookeeperFellow.h"
#include "User.h"
#include "protoFile/FriendServer.pb.h"

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/Buffer.h>
#include <muduo/base/Timestamp.h>

#include <sqlPool/connectPool.h>

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>

class FriendServer {
public:
    FriendServer(std::string&& ip, uint16_t port);

public:
    // 服务器运行
    void run();

    // 读写事件回调函数
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp);

    // 连接事件回调函数
    void onConnect(const muduo::net::TcpConnectionPtr& conn);

public:
    // 获取userid 用户的好友列表
    std::vector<User> getFriendlist(int userid);

    // 获得userid用户信息
    User getUserInfo(int userid);

    // userid 的用户添加好友 friendid
    void addFriend(int userid, int friendid);

    // 删除userid用户的好友 friendid
    void deleteFriend(int userid, int friendid);

private:
    std::string ip_;

    uint16_t port_;

    muduo::net::EventLoop loop_;

    ConnectPool* sqlPool_;
};