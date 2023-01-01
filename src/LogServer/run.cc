#include "LogServer.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcprovider.h>
#include <myrpc/myrpccontroller.h>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new LogServer);
    provider.Run();

    return 0;
}