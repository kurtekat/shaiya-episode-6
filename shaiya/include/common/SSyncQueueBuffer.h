#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // thanks, Cups :P
    struct SSyncQueueBuffer
    {
        void* head;
        void* tail;
        CRITICAL_SECTION cs;
        UINT32 count;
    };
    #pragma pack(pop)
}
