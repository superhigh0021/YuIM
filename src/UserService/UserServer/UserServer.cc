#include "UserServer.h"

constexpr int BUFF_SIZE = 128;

UserServer::UserServer(const std::string& ip, uint16_t port) :
    stub_(new MyrpcChannel()), ip_(ip), port_(port) {
    sqlPool_ = ConnectPool::getInst();

    if (sqlPool_ == nullptr) {
        ik::LogRequest request;
        request.set_name("UserServer");
        request.set_msg("create mysql pool error!");
        stub_.Log_ERROR(nullptr, &request, nullptr, nullptr);
    }
}

void UserServer::run() {
    // 初始化网络层
    muduo::net::InetAddress address(ip_.c_str(), port_);
    muduo::net::TcpServer server(&loop_, address, "UserServer");

    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
        msgCallback(conn, buffer, stamp);
    });

    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn) {
        connCallback(conn);
    });

    // 注册zookeeper节点
    ZKClient zkClient;
    zkClient.start();
    std::string serverPath = "/UserService/server";
    char buffer[BUFF_SIZE] = {0};
    ::sprintf(buffer, "%s:%d", ip_.c_str(), port_);

    if (zkClient.create(serverPath, buffer, strlen(buffer), ZOO_EPHEMERAL) == false) {
        ik::LogRequest request;
        std::string name = "UserServer";
        name += buffer;
        request.set_name(name);
        request.set_msg("zookeeper connect error!");
        google::protobuf::Empty response;
        stub_.Log_ERROR(nullptr, &request, &response, nullptr);
    } else {
        ik::LogRequest request;
        std::string name = "UserServer";
        name += buffer;
        request.set_name(name);
        request.set_msg("zookeeper connect!");
        google::protobuf::Empty response;
        stub_.Log_ERROR(nullptr, &request, &response, nullptr);
    }

    // 开启事件循环
    server.setThreadNum(4);
    server.start();
    loop_.loop();
}

void UserServer::msgCallback(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp stamp) {
    // 反序列化
    std::string message = buffer->retrieveAllAsString();
    ik_UserServer::Request request;
    request.ParseFromString(message);

    if (request.type() == "Login") {
        // 登录业务
        ik_UserServer::LoginRequest loginRequest;
        loginRequest.ParseFromString(request.request());
        int id = loginRequest.id();
        std::string password = loginRequest.password();

        // 执行具体的Login方法，执行成功is_success被设置为true
        ik_UserServer::LoginResponse loginResponse;
        if (Login(id, password) == true) {
            loginResponse.set_is_success(true);
        } else {
            loginResponse.set_is_success(false);
            auto msg = loginResponse.mutable_msg();
            msg->set_message("login error");
        }

        // 序列化结果并将结果返回
        std::string sendStr = loginResponse.SerializeAsString();
        conn->send(sendStr.c_str(), sendStr.size());
    } else if (request.type() == "LoginOut") {
        // 注销业务
        ik_UserServer::LoginOutRequest outRequest;
        outRequest.ParseFromString(request.request());
        int id = outRequest.id();

        LoginOut(id);
    } else {
        // 其他业务，此处没有，所以向LogServer服务器打印一条日志信息
        ik::LogRequest request;
        request.set_name("UserServer");
        message += ip_.c_str();
        message += " not have this service!";
        request.set_msg(message);
        stub_.Log_ERROR(nullptr, &request, nullptr, nullptr);
    }
}

// 连接事件的回调函数
void UserServer::connCallback(const muduo::net::TcpConnectionPtr& conn) {
    if (!conn->connected()) {
        // 和rpc client断开连接
        conn->shutdown();
    }
}

// 登录
bool UserServer::Login(int id, const std::string& password) {
    auto conn = sqlPool_->getConnect();

    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "select * from User where id = %d and password = '%s'", id, password.c_str());
    auto res = conn->query(sql);
    if (res == nullptr) {
        mysql_free_result(res);
        return false;
    } else {
        // 释放结果，否则会失败
        mysql_free_result(res);
        // 更新用户状态为在线
        ::bzero(sql, BUFF_SIZE);
        ::sprintf(sql, "update User set state='online' where id = %d", id);

        if (conn->update(sql) == false) {
            ik::LogRequest request;
            request.set_name("UserServer");
            request.set_msg(sql, strlen(sql));
            google::protobuf::Empty response;
            stub_.Log_ERROR(nullptr, &request, &response, nullptr);
            return false;
        }
        return true;
    }
}

// 注销
void UserServer::LoginOut(int id) {
    // 更新数据库User 状态为offline
    auto conn = sqlPool_->getConnect();
    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "update User set state = 'offline' where id = %d", id);
    conn->update(sql);
}

// 注册 成功返回注册的账户，失败返回-1
int UserServer::Register(const std::string& name, const std::string& password) {
    auto conn = sqlPool_->getConnect();
    char sql[BUFF_SIZE] = {0};
    ::sprintf(sql, "insert into User(name,password) values('%s','%s')", name.c_str(), password.c_str());

    if (conn->update(sql) == false) {
        ik::LogRequest request;
        request.set_name("UserServer");
        request.set_msg(sql, strlen(sql));
        stub_.Log_ERROR(nullptr, &request, nullptr, nullptr);
        return false;
    }
    // 这个api可以获取上一次插入的自增id
    return mysql_insert_id(conn->getConnection());
}