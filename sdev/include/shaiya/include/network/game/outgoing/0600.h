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
        ULONG objectId;
        ULONG targetId;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MobRecoverAddOutgoing
    {
        UINT16 opcode{ 0x610 };
        ULONG objectId;
        UINT32 addHealth;
    };
    #pragma pack(pop)
}
