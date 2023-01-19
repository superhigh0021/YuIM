#include "FriendServer.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

int main(int argc, char** argv) {
    MyrpcApplication::getInstance().Init(argc, argv);
    auto configure = MyrpcApplication::getConfig();
    std::string ip = configure.Load("server_ip");
    int port = atoi(configure.Load("server_port").c_str());
    FriendServer server(std::move(ip), port);

    server.run();

    return 0;
}