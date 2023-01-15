#include "OfflineService.h"

#include <myrpc/myrpcprovider.h>
#include <myrpc/myrpcapplication.h>

auto main(int argc, char** argv) -> int {
    MyrpcApplication::getInstance().Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new OfflineService);
    provider.Run();

    return 0;
}