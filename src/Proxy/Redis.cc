#include "Redis.h"

#include <iostream>

// 初始化Redis连接信息
RedisCli::RedisCli() {
    MyrpcConfig configure = MyrpcApplication::getInstance().getConfig();
    ip_ = configure.Load("redis_ip");
    port_ = atoi(configure.Load("redis_port").c_str());
}

// 释放连接
RedisCli::~RedisCli() {
    redisFree(get_channel_);
    redisFree(set_channel_);
}

// 初始化get_channel_、set_channel_连接
bool RedisCli::connect() {
    get_channel_ = redisConnect(ip_.c_str(), port_);
    if (get_channel_ == nullptr) {
        return false;
    }

    set_channel_ = redisConnect(ip_.c_str(), port_);
    if (set_channel_ == nullptr) {
        return false;
    }

    return true;
}

// 判断某个账号是否在线
bool RedisCli::isExist(int id) {
    if (getHost(id) == "") {
        return false;
    } else {
        return true;
    }
}

// 根据账号得到它上线的服务器
std::string RedisCli::getHost(int id) {
    redisReply* reply = static_cast<redisReply*>(redisCommand(get_channel_, "get %d", id));
    if (reply == nullptr) {
        return "";
    }
    std::string result = reply->str;
    freeReplyObject(reply);

    return result;
}

// 设置账号及其登录的服务器
bool RedisCli::setHost(int id, std::string host) {
    redisReply* reply = static_cast<redisReply*>(redisCommand(set_channel_, "set %d %s", id, host.c_str()));
    if (reply == nullptr) {
        return false;
    }
    freeReplyObject(reply);
    return true;
}

// 删除用户的信息
bool RedisCli::delHost(int id) {
    redisReply* reply = static_cast<redisReply*>(redisCommand(set_channel_, "del %d", id));
    if (reply == nullptr) {
        return false;
    }
    freeReplyObject(reply);
    return true;
}