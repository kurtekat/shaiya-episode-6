#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MobAttack
    {
        UINT16 opcode{ 0x605 };
        UINT8 damageType;
        // CMob->id
        ULONG mobId;
        CharId targetId;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)
}
