#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups :P
    struct SSyncQueueBufferSend
    {
        void* head;
        void* tail;
        UINT32 length;
        CRITICAL_SECTION cs;
        UINT32 count;
    };
    #pragma pack(pop)
}
