#pragma once
#include <cstdio>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SLog
    {
        PAD(4);
        FILE* stream;          //0x04
        CRITICAL_SECTION cs8;  //0x08
        // 0x20

        static bool PrintFileDirect(SLog* log, const char* fmt, ...);
    };
    #pragma pack(pop)
}
