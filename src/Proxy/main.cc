#include <signal.h>

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcconfig.h>

#include "ProxyService.h"

// 处理服务器 Ctrl+C 结束后，重置user状态信息
void resetHandler(int) {
    ProxyService::getInstance().reset();
    exit(0);
}

auto main(int argc, char** argv) -> int {
    MyrpcApplication::Init(argc, argv);
    MyrpcConfig config = MyrpcApplication::getInstance().getConfig();
    std::string ip = config.Load("server_ip");
    uint16_t port = atoi(config.Load("server_port").c_str());

    ::signal(SIGINT, resetHandler);

    ProxyService::getInstance();

    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr(ip, port);
    ProxyServer server(loop, addr, "ProxyServer");

    server.start();
    loop.loop();

    return 0;
}