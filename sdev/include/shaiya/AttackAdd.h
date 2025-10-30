#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AttackAdd
    {
        int32_t hitRate;
        int32_t power;
        int32_t evasionRate;
        int32_t defense;
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(AttackAdd) == 0x10);
}