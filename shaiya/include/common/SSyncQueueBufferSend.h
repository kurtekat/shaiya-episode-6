#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups :P
    struct SSyncQueueBufferSend
    {
        void* head;           //0x00
        void* tail;           //0x04
        UINT32 length;        //0x08
        CRITICAL_SECTION cs;  //0x0C
        UINT32 count;         //0x24
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncQueueBufferSend) == 0x28);
}
