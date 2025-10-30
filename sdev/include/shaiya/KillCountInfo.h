#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // stKCInfo
    struct KillCountInfo
    {
        int32_t index;       //0x00
        int32_t count;       //0x04
        int32_t countNext;   //0x08
        tick32_t resetTime;  //0x0C
        tick32_t sendTime;   //0x10
        PAD(112);
        // 0x84
    };
    #pragma pack(pop)

    static_assert(sizeof(KillCountInfo) == 0x84);
}
