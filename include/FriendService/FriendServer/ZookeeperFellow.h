#pragma once

#include <zookeeper/zookeeper.h>

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

#include <semaphore.h>
#include <string>

class ZKClient {
public:
    ZKClient();
    ~ZKClient();

    // 和zookeeper建立连接
    bool start();

    // 在zkserver中根据指定的path创建znode节点
    bool create(const std::string& path, const char* data, int dataLen, int state = 0);

    // 根据参数路径获得值
    std::string getData(const std::string& path);

private:
    zhandle_t* zkhandle_; // zookeeper连接句柄
};