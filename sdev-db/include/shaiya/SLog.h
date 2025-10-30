#pragma once
#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SLog
    {
        void* vftable;        //0x00
        FILE* stream;         //0x04
        CRITICAL_SECTION cs;  //0x08
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(SLog) == 0x20);
}
