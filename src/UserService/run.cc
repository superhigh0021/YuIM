#include "UserService.h"

#include <myrpc/myrpcprovider.h>
#include <myrpc/myrpcapplication.h>

#include <string>
#include <unistd.h>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().Init(argc, argv);
    RpcProvider provider;
    provider.NotifyService(new UserService);
    provider.Run();

    return 0;
}