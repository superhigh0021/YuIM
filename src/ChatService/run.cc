#include "ChatServer.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().getConfig();
    MyrpcConfig configure = MyrpcApplication::getInstance().getConfig();

    std::string redisIp = configure.Load("redis_ip");
    uint16_t redisPort = atoi(configure.Load("redis_port").c_str());
    std::string ip = configure.Load("server_ip");
    uint16_t port = atoi(configure.Load("server_port").c_str());

    ChatServer server(std::move(redisIp), redisPort);
    server.run(std::move(ip), port);
}