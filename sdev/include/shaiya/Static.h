#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct Static
    {
        static void ConvTime(uint_t time/*eax*/, SYSTEMTIME* output/*ecx*/);
        static uint_t ConvTime(SYSTEMTIME* time/*ecx*/);
        static uint_t GetSystemTime();
    };
}
