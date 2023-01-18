#include "ZookeeperFellow.h"
#include "GroupServer.pb.h"
#include "User.h"

#include <sqlPool/connectPool.h>

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/Buffer.h>
#include <muduo/base/Timestamp.h>

#include <string>
#include <memory>
#include <vector>
#include <functional>

class GroupServer {
public:
    // 初始化server信息
    GroupServer(std::string&& ip, uint16_t port);

    // 开始运行服务
    void run();

    // 绑定连接事件
    void onConnect(const muduo::net::TcpConnectionPtr& conn);

    // 绑定读写事件
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp);

public:
    // 将userid所代表的用户添加到groupid的群里
    bool addGroup(int userid, int groupid);

    // 创建群、群名为groupName、返回群号
    int createGroup(int userid, std::string&& groupName);

    // 在groupid的群里删除userid这一列
    bool quitGroup(int userid, int groupid);

    // 得到群组中所有用户信息
    std::vector<User> getGroupUsers(int groupid);

private:
    std::string ip_;

    uint16_t port_;

    muduo::net::EventLoop loop_;

    ZKClient zkClient_;

    ConnectPool* pool_;
};