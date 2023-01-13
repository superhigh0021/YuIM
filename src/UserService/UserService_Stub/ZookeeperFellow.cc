#include "ZookeeperFellow.h"

#include <iostream>

constexpr int BUFF_SIZE = 128;

// zk_init函数的异步回调函数
void init_watcher(zhandle_t* handler, int type, int state, const char* path, void* watcher_context) {
    if (type == ZOO_SESSION_EVENT) {
        if (state == ZOO_CONNECTED_STATE) {
            // 连接成功,发送一个信号
            sem_t* sem = (sem_t*)zoo_get_context(handler);
            sem_post(sem);
        }
    }
}

ZKClient::ZKClient() :
    zkhandle_(nullptr) {
}

ZKClient::~ZKClient() {
    if (zkhandle_ != nullptr) {
        zookeeper_close(zkhandle_);
    }
}

// 和zkserver建立连接
bool ZKClient::start() {
    auto& configure = MyrpcApplication::getInstance().getConfig();
    std::string ip = configure.Load("zookeeper_ip");
    std::string host = configure.Load("zookeeper_port");

    std::string connStr = ip + ":" + host;
    zkhandle_ = zookeeper_init(connStr.c_str(), init_watcher, 300000, 0, nullptr, 0);
    if (zkhandle_ == nullptr) {
        return false;
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(zkhandle_, &sem);

    sem_wait(&sem);
    return true;
}

// 在zkserver中根据指定的path创建znode节点
bool ZKClient::create(const std::string& path, const char* data, int dataLen, int state) {
    char pathBuffer[BUFF_SIZE] = {0};
    int buffLen = sizeof pathBuffer;
    int tail = 1;

    std::string tailStr = path + std::to_string(tail);

    int flag = zoo_create(zkhandle_, tailStr.c_str(), data, dataLen, &ZOO_OPEN_ACL_UNSAFE, state, pathBuffer, buffLen);
    if (flag == ZOK) {
        return true;
    } else {
        return false;
    }
}

std::string ZKClient::getData(const std::string& path) {
    char buf[BUFF_SIZE] = {0};
    int buffLen = sizeof buf;

    int flag = zoo_get(zkhandle_, path.c_str(), 0, buf, &buffLen, nullptr);
    if (flag == ZOK) {
        return buf;
    } else {
        return "";
    }
}