#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct Static
    {
        static void ConvTime(uint time/*eax*/, SYSTEMTIME* output/*ecx*/);
        static uint ConvTime(SYSTEMTIME* time/*ecx*/);
        static uint GetSystemTime();
    };
}
