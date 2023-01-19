#pragma once

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

#include <hiredis/hiredis.h>

#include <string>

class RedisCli {
public:
    // 初始化Redis连接信息
    RedisCli();

    // 释放连接
    ~RedisCli();

    // 初始化get_channel_、set_channel_连接
    bool connect();

    // 判断某个账号是否在线
    bool isExist(int id);

    // 根据账户信息得到它上线的服务器
    std::string getHost(int id);

    // 设置账户及其登录的服务器
    bool setHost(int id, std::string host);

    // 删除用户的信息
    bool delHost(int id);

private:
    redisContext* get_channel_;

    redisContext* set_channel_;

    std::string ip_;

    uint16_t port_;
};