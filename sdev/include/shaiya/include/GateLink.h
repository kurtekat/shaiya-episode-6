#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GateLink
    {
        uint16_t mapId;    //0x00
        PAD(2);
        float x;           //0x04
        float y;           //0x08
        float z;           //0x0C
        String<256> name;  //0x10
        uint32_t money;    //0x110
        // 0x114
    };
    #pragma pack(pop)

    static_assert(sizeof(GateLink) == 0x114);
}
