#include "ZookeeperMaster.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 128

// zk_init 函数的异步回调函数，全局的watcher观察器，handler表示zkserver给zkclient的通知
void init_watcher(zhandle_t* handler, int type, int state, const char* path, void* watcher_context) {
    if (type == ZOO_SESSION_EVENT) {
        // 回调的消息类型是和会话相关的消息类型
        if (state == ZOO_CONNECTED_STATE) {
            // zkclient和zkserver连接成功才建立会话
            sem_t* sem = (sem_t*)(zoo_get_context(handler)); // 指定handle获取信号量
            sem_post(sem);                                   // 信号量资源加1
        }
    }
}

ZKMaster::ZKMaster(const std::string& path) :
    zkhandle_(nullptr), currentService_(0), path_(path) {
}

ZKMaster::~ZKMaster() {
    if (zkhandle_ != nullptr) {
        zookeeper_close(zkhandle_);
    }
}

// 和zkserver连接
bool ZKMaster::start() {
    std::string host = MyrpcApplication::getInstance().getConfig().Load("zookeeper_ip");
    std::string port = MyrpcApplication::getInstance().getConfig().Load("zookeeper_port");
    std::string connstr = host + ":" + port;
    // std::cout << connstr << "\n";

    /*
     * zookeeper_mt：多线程版本
     * zookeeper的API客户端程序提供了三个线程：
     * API调用线程 也就是当前线程 也就是调用的线程 zookeeper_init
     * 网络I/O线程  zookeeper_init调用了pthread_create  poll专门连接网络
     * watcher回调线程 当客户端接收到zkserver的响应，再次调用pthread_create，产生watcher回调线程
     */

    // 返回handle，会话的创建是异步的，并不是返回成功了就表示连接成功，而是等到回调函数真正接收到zkserver响应进行回调
    zkhandle_ = zookeeper_init(connstr.c_str(), init_watcher, 30000, 0, nullptr, 0);
    if (zkhandle_ == nullptr) {
        // 表示发起的动作没有产生，即传入参数有问题
        std::cout << "zookeeper_init error!\n";
        return false;
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(zkhandle_, &sem); // 创建handle成功后，向handle设置上下文，添加额外的信息

    sem_wait(&sem); // 初值为0的信号量是用来控制执行次序的

    // 初始化节点信息
    getFollow();

    return true;
}

// 在zkserver中根据指定的path创建znode节点
bool ZKMaster::createMaster(const std::string& masterName) {
    std::string path = "/" + masterName;
    char pathBuffer[BUFF_SIZE] = {0};
    int bufLen = sizeof(pathBuffer);

    // int flag = zoo_create(zkhandle_, path.c_str(), "", 0, &ZOO_OPEN_ACL_UNSAFE, 0, pathBuffer, bufLen);
    // if (flag == ZOK) {
    //     return true;
    // } else {
    //     return false;
    // }

    int flag;
    // 先判断path表示的znode节点是否存在，如果存在就不再重复创建
    flag = zoo_exists(zkhandle_, path.c_str(), 0, nullptr);
    if (flag == ZNONODE) {
        // 表示path的znode节点不存在
        flag = zoo_create(zkhandle_, path.c_str(), "", 0, &ZOO_OPEN_ACL_UNSAFE, 0, pathBuffer, bufLen);
        // handle、路径、数据、数据长度。flag默认创建永久性
        if (flag == ZOK) {
            std::cout << "znode create success, path:" << path << "\n";
            return true;
        } else {
            std::cout << "flag:" << flag << "\n";
            std::cout << "znode create error... path:" << path << "\n";
            return false;
        }
    }
    return true;
}

// 每秒更新服务列表
void ZKMaster::getFollow() {
    if (zkhandle_ == nullptr) {
        std::cout << "zkhandle is nullptr, cannot continue!\n";
    }
    String_vector followers;
    zoo_get_children(zkhandle_, path_.c_str(), 0, &followers);

    std::unordered_map<std::string, std::string> tmp;
    totalServices_ = followers.count;

    for (int i = 0; i < totalServices_; ++i) {
        std::cout << followers.data[i] << "\n";
        std::string znodeName = followers.data[i];
        std::string znodePath = path_ + "/" + znodeName;
        std::string ipPort = getZnodeData(znodePath);
        tmp[znodeName] = ipPort;
    }

    {
        std::lock_guard lock(mutex_);
        followers_.swap(tmp);
    }
}

// 根据指定的path，获取znode节点的值
std::string ZKMaster::getZnodeData(const std::string& path) {
    char buf[BUFF_SIZE] = {0};
    int bufLen = sizeof buf;

    int flag = zoo_get(zkhandle_, path.c_str(), 0, buf, &bufLen, nullptr);
    if (flag != ZOK) {
        std::cout << "get znode error... path:" << path << "\n";
        return "";
    } else {
        return buf;
    }
}

// 得到一个可用的服务节点，并与之创建一个文件描述符，返回文件描述符
int ZKMaster::getService() {
    if (totalServices_ == 0) {
        return -1;
    }
    std::string hostData;

    {
        std::lock_guard lock(mutex_);
        // 获取当前应该服务的节点
        auto it = followers_.begin();
        for (int i = 0; i < currentService_; ++i) {
            ++it;
        }
        currentService_ = (currentService_ + 1) % (totalServices_ + 1);

        hostData = it->second;
    }

    int hostIndex = hostData.find(":");
    if (hostIndex == -1) {
        return -1;
    }

    // 取得ip和port
    std::string ip = hostData.substr(0, hostIndex);
    uint16_t port = atoi(hostData.substr(hostIndex + 1, hostData.size() - hostIndex).c_str());

    // 建立套接字并连接
    int clientFd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFd == -1) {
        close(clientFd);
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(clientFd, (struct sockaddr*)&server_addr, sizeof server_addr) == -1) {
        close(clientFd);
        return -1;
    } else {
        return clientFd;
    }
}