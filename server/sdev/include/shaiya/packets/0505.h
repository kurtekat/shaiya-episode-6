#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RecoverAddOutgoing
    {
        UINT16 opcode{ 0x505 };
        ULONG charId;
        int health;
        int mana;
        int stamina;
    };
    #pragma pack(pop)
}
