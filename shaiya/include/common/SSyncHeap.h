#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    struct SSyncHeap
    {
        PAD(4);
        UINT32 allocCount;
        UINT32 freeCount;
        CRITICAL_SECTION cs;
    };
    #pragma pack(pop)
}
