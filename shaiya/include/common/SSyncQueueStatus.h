#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SSyncQueueStatus
    {
        PAD(8);
        CRITICAL_SECTION cs;
        UINT32 count;
        // 0x24
    };
    #pragma pack(pop)
}
