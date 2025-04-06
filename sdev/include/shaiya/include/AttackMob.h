#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AttackMob
    {
        bool32_t disabled;
        int32_t hitRate;
        int32_t power;
        int32_t evasionRate;
        int32_t defense;
        int32_t criticalHitRate;
        int32_t criticalEvasionRate;
        // 0x1C
    };
    #pragma pack(pop)

    static_assert(sizeof(AttackMob) == 0x1C);
}
