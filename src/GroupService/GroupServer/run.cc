#include "GroupServer.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().Init(argc, argv);
    auto config = MyrpcApplication::getInstance().getConfig();
    std::string ip = config.Load("server_ip");
    uint16_t port = atoi(config.Load("server_port").c_str());

    GroupServer server(std::move(ip), port);
    server.run();
    return 0;
}