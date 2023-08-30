#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserStatus
    {
        UINT16 opcode{ 0x526 };
        UINT32 strength;
        UINT32 reaction;
        UINT32 intelligence;
        UINT32 wisdom;
        UINT32 dexterity;
        UINT32 luck;
        UINT32 minAttackPower;
        UINT32 maxAttackPower;
        UINT32 minMagicPower;
        UINT32 maxMagicPower;
        UINT32 defense;
        UINT32 resistance;
    };
    #pragma pack(pop)
}
