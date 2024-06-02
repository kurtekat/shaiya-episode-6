#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SThread
    {
        PAD(4);
        HANDLE handle;  //0x04
        bool running;   //0x08
        PAD(3);
        HANDLE hEvent;  //0x0C
        PAD(24);
        // 0x28
    };
    #pragma pack(pop)
}
