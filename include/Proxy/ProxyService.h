#pragma once

#include "Redis.h"
#include "ProxyServer.h"
#include "ZookeeperMaster.h"

#include "LogServer.pb.h"
#include "ChatServer.pb.h"
#include "UserService.pb.h"
#include "FriendService.pb.h"
#include "GroupService.pb.h"
#include "OfflineService.pb.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>
#include <myrpc/myrpccontroller.h>
#include <myrpc/myrpcchannel.h>

#include <unordered_map>
#include <functional>
#include <string>
#include <mutex>

using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr& conn,
                                      std::string& recvStr,
                                      muduo::Timestamp time)>;

// 单例设计
class ProxyService {
public:
    static ProxyService& getInstance() {
        static ProxyService service;
        return service;
    }

public:
    ProxyService(const ProxyService&) = delete;
    ProxyService& operator=(ProxyService&) = delete;

public:
    // 登录
    void login(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 注册
    void regist(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 注销业务
    void loginOut(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 一对一聊天业务
    void oneChat(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 添加好友业务
    void addFriend(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 删除好友
    void deleteFriend(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 获取用户信息
    void getUserInfo(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 获取好友列表
    void getFriendList(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 读取离线消息
    void readOfflineMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 创建群组
    void createGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 加入群组
    void addGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 退出群
    void quitGroup(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 获得群用户信息
    void getGroupUsers(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 聊天消息
    void chatMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

    // 转发而来的消息
    void conveyMsg(const muduo::net::TcpConnectionPtr& conn, std::string& recvBuf, muduo::Timestamp time);

public:
    // 获得消息对应的处理器
    MsgHandler getHandler(std::string msgType);

    // 处理客户端异常退出
    void clientCloseException(const muduo::net::TcpConnectionPtr& conn);

    // 服务器异常、业务重置
    void reset();

private:
    ProxyService();

private:
    std::unordered_map<std::string, MsgHandler> msgHandlerMap_; // 存储事件以及事件对应的回调函数

    std::unordered_map<int, muduo::net::TcpConnectionPtr> userConnectionMap_; // 存储登录用户以及其对应的连接句柄

    std::mutex mutex_;

private:
    RedisCli redisClient_; // 连接redis服务器

    ZKMaster master_; // 连接zookeeper服务器

private:
    ik_GroupService::GroupServiceRpc_Stub groupStub_;
    ik_UserService::UserServiceRpc_Stub userStub_;
    ik_FriendService::FriendServiceRpc_Stub friendStub_;
    ik_OfflineService::OfflineServiceRpc_Stub offlineStub_;
    ik::LogServerRpc_Stub logStub_;
};