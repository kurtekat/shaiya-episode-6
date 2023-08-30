#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RecoverAdd
    {
        UINT16 opcode; // 0x505
        ULONG charId;
        UINT32 health;
        UINT32 mana;
        UINT32 stamina;
    };
    #pragma pack(pop)
}
