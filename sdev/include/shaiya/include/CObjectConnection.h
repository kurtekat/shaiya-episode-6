#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/CObject.h"
#include "include/shaiya/include/SConnectionCustomRecv.h"
#include "include/shaiya/include/SSyncQueueBufferPriority.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CObjectConnection : SConnectionCustomRecv, CObject
    {
        // 0xF8
        SSyncQueueBufferPriority sendPriorityQueue;
        PAD(8);
        // 0x128
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectConnection) == 0x128);
}
