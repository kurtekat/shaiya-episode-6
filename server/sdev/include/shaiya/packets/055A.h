#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct TownTeleportScroll
    {
        UINT16 opcode{ 0x55A };
        UINT8 bag;
        UINT8 slot;
        UINT8 location;
    };
    #pragma pack(pop)
}
