#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct SkillUseState : UINT8
    {
        Triggered = 1,
        Stopped = 3
    };

    struct SkillUseOutgoing
    {
        UINT16 opcode{ 0x511 };
        UINT8 targetType;
        CharId senderId;
        CharId targetId;
        UINT16 skillId;
        UINT8 skillLv;
        UINT16 health;
        UINT16 stamina;
        UINT16 mana;
        #ifdef WITH_EXTENDED_0511
        SkillUseState state;
        #endif
    };
    #pragma pack(pop)
}
