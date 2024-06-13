#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SkillAbility70
    {
        UINT16 skillId;
        UINT8 skillLv;
        bool triggered;
        DWORD keepTick;
    };
    #pragma pack(pop)
}
