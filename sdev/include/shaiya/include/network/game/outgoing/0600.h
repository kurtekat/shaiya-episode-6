#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MobAttackOutgoing
    {
        UINT16 opcode{ 0x605 };
        UINT8 damageType;
        // mob
        ULONG id;
        ULONG targetId;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)
}
