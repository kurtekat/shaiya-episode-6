#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    struct SSyncHeap
    {
        PAD(4);
        UINT32 allocCount;    //0x04
        UINT32 freeCount;     //0x08
        CRITICAL_SECTION cs;  //0x0C
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncHeap<void>) == 0x24);
}
