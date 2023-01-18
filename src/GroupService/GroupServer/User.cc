#include "User.h"

// 设置用户id
void User::setId(int id) {
    id_ = id;
}

// 设置用户名
void User::setName(std::string &&name) {
    name_ = name;
}

// 获取用户id
int User::getId() const {
    return id_;
}

// 获取用户名
std::string User::getName() const {
    return name_;
}

