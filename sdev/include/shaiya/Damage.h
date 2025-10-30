#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct Damage : SNode
    {
        uint8_t type;    //0x08
        PAD(3);
        uint32_t id;     //0x0C
        int32_t damage;  //0x10
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(Damage) == 0x14);
}
