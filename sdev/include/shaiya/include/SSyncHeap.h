#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class T>
    struct SSyncHeap
    {
        T* first;             //0x00
        int32_t allocCount;   //0x04
        int32_t nodeCount;    //0x08
        CRITICAL_SECTION cs;  //0x0C
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncHeap<void>) == 0x24);
}
