#include "OfflineServer.pb.h"
#include "ZookeeperFellow.h"

#include <sqlPool/connectPool.h>

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Timestamp.h>

#include <string>
#include <vector>
#include <memory>

class OfflineServer {
public:
    // 初始化配置等信息
    OfflineServer(std::string&& ip, uint16_t port);

    // 开始服务
    void run();

    // 读写事件回调函数
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp);

    // 连接事件回调函数
    void on_connect(const muduo::net::TcpConnectionPtr& conn);

public:
    // 写离线消息
    bool writeOfflineMsg(int friendId, std::string&& msg);

    // 读离线消息
    std::vector<std::string> readOfflineMsg(int myid);

private:
    std::string ip_;

    uint16_t port_;

    muduo::net::EventLoop loop_;

    ZKClient zkClient_;

    ConnectPool* pool_;
};