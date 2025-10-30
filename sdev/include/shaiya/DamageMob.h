#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct DamageMob : SNode
    {
        uint8_t type;      //0x08
        PAD(3);
        uint32_t userId;   //0x0C
        uint32_t damage;   //0x10
        uint32_t aggro;    //0x14
        uint32_t partyId;  //0x18
        // 0x1C
    };
    #pragma pack(pop)

    static_assert(sizeof(DamageMob) == 0x1C);
}
