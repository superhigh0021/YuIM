#include "OfflineServer.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

auto main(int argc, char** argv) -> int {
    auto& rpcAppInst = MyrpcApplication::getInstance();
    rpcAppInst.Init(argc, argv);
    auto config = rpcAppInst.getConfig();
    std::string ip = config.Load("server_ip");
    uint16_t port = atoi(config.Load("server_port").c_str());

    OfflineServer server(std::move(ip), port);
    server.run();

    return 0;
}