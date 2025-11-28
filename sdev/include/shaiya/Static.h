#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct Static
    {
        static void ConvTime(time32_t time/*eax*/, SYSTEMTIME* output/*ecx*/);
        static time32_t ConvTime(SYSTEMTIME* time/*ecx*/);
        static time32_t GetSystemTime();
    };
}
