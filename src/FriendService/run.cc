#include "FriendService.h"

#include <myrpc/myrpcapplication.h>
#include <myrpc/myrpcprovider.h>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().Init(argc, argv);
    RpcProvider provider;
    provider.NotifyService(new FriendService);

    provider.Run();
    return 0;
}