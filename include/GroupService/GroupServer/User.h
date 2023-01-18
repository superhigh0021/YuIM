#pragma once

#include <string>

class User {
public:
    // 设置用户id
    void setId(int id);

    // 设置用户名
    void setName(std::string&& name);

    // 获取用户id
    int getId() const;

    // 获得用户名
    std::string getName() const;

private:
    int id_;
    std::string name_;
};