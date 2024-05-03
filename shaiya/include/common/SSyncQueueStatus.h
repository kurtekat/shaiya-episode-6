#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SSyncQueueStatus
    {
        PAD(8);
        CRITICAL_SECTION cs;  //0x08
        UINT32 count;         //0x20
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncQueueStatus) == 0x24);
}
