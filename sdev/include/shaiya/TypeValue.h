#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SkillTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct TypeValue
    {
        SkillAbilityType type;
        PAD(1);
        uint16_t value;
    };
    #pragma pack(pop)

    static_assert(sizeof(TypeValue) == 0x4);
}
