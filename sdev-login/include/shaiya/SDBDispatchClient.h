#pragma once
#include <shaiya/include/common.h>
#include "SSyncQueueStatus.h"

namespace shaiya
{
    struct SDBDispatcher;

    #pragma pack(push, 1)
    struct SDBDispatchClient
    {
        void* vftable;              //0x00
        SSyncQueueStatus jobQueue;  //0x08
        SDBDispatcher* dispatcher;  //0x28
        int32_t jobCount;           //0x2C
        // 0x30
    };
    #pragma pack(pop)

    static_assert(sizeof(SDBDispatchClient) == 0x30);
}
