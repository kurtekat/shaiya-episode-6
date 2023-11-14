#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserTargetIncoming
    {
        UINT16 opcode{ 0x302 };
        CharId targetId;
    };

    struct UserTargetOutgoing
    {
        UINT16 opcode{ 0x302 };
        CharId targetId;
        UINT32 maxHealth;
        UINT32 health;
    };
    #pragma pack(pop)
}
