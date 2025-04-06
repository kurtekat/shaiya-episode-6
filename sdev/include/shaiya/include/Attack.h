#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Attack
    {
        bool32_t disabled;
        int32_t block;
        int32_t blockValue;
        int32_t mirrorSkillId;
        int32_t mirrorSkillLv;
        int32_t hitRate;
        int32_t power;
        int32_t evasionRate;
        int32_t defense;
        int32_t criticalHitRate;
        int32_t criticalEvasionRate;
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(Attack) == 0x2C);
}
