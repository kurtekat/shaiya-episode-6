#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SSyncQueueStatus.h>

namespace shaiya
{
    struct SDBDispatcher;

    #pragma pack(push, 1)
    struct SDBDispatchClient
    {
        PAD(4);
        SSyncQueueStatus queueStatus;
        SDBDispatcher* dispatcher;
        PAD(4);
        // 0x30
    };
    #pragma pack(pop)
}
