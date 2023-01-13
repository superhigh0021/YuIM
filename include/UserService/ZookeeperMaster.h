#pragma once

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

#include <zookeeper/zookeeper.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <unordered_map>

class ZKMaster {
public:
    ZKMaster(const std::string& path);
    ~ZKMaster();

    // 与zkserver建立连接
    bool start();

    // 在zkserver根据指定的path创建znode节点
    bool createMaster(const std::string& masterName);

    // 每秒更新服务列表
    void getFollow();

    // 得到znode节点对应的data值
    std::string getZnodeData(const std::string& path);

    // 得到一个可用的服务节点，并创建一个文件描述符，返回文件描述符
    int getService();

private:
    zhandle_t* zkhandle_;
    std::unordered_map<std::string, std::string> followers_; // 存储从节点

    int currentService_; // 当前应该是哪个节点服务
    int totalServices_;  // 总共有多少节点服务

    std::string path_; // 当前服务路径

    std::mutex mutex_;
};