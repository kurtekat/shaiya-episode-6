#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RecoverSetOutgoing
    {
        UINT16 opcode{ 0x521 };
        UINT32 health;
        UINT32 mana;
        UINT32 stamina;
    };
    #pragma pack(pop)
}
