#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups :P
    struct SSyncQueueBuffer
    {
        void* head;           //0x00
        void* tail;           //0x04
        CRITICAL_SECTION cs;  //0x08
        UINT32 count;         //0x20
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncQueueBuffer) == 0x24);
}
