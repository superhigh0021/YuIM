#include "LogSend.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

#include <cstdlib>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::Init(argc, argv);
    MyrpcConfig& configure = MyrpcApplication::getInstance().getConfig();
    std::string ip = configure.Load("LogSend_ip");
    uint16_t port = atoi(configure.Load("LogSend_port").c_str());

    LogSend server;
    server.run(ip, port);
    return 0;
}