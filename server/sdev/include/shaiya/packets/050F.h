#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SkillKeep
    {
        UINT16 opcode{ 0x50F };
        ULONG charId;
        UINT16 skillId;
        UINT8 skillLv;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)
}
