#pragma once

#include "ZookeeperFellow.h"
#include "Redis.h"
#include "protoFile/LogServer.pb.h"
#include "protoFile/ChatServer.pb.h"
#include "protoFile/ProxyServer.pb.h"
#include "protoFile/OfflineService.pb.h"

#include <myrpc/myrpcchannel.h>
#include <myrpc/myrpcchannel.h>

#include <google/protobuf/empty.pb.h>

#include <muduo/net/EventLoop.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/TcpConnection.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unordered_map>
#include <functional>
#include <string>

class ChatServer {
public:
    ChatServer(std::string&& redisIp, uint16_t redisPort);

    // 开启服务
    void run(std::string&& ip, uint16_t port);

    // 读写事件回调函数
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp);

    // 连接事件回调函数
    void onConnect(const muduo::net::TcpConnectionPtr& conn);

public:
    // 根据host建立连接
    int establishConnection(std::string&& host);

private:
    ZKClient zkClient_;

    RedisCli redisClient_;

    muduo::net::EventLoop loop_;

    // 存储抽象服务节点chatservice以及与其连接对应的socket
    std::unordered_map<std::string, int> channelMap_;

    ik::LogServerRpc_Stub stub_;

    ik_OfflineService::OfflineServiceRpc_Stub offlineStub_;
};