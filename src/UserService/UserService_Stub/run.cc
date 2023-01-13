#include "UserServer.h"

#include <myrpc/myrpcapplication.h>
#include <cstdlib>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::Init(argc, argv);
    auto configure = MyrpcApplication::getConfig();

    std::string ip = configure.Load("server_ip");
    uint16_t port = atoi(configure.Load("server_port").c_str());
    UserServer server(ip, port);
    server.run();
}