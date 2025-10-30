#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CMonsterData
    {
        PAD(20);
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(CMonsterData) == 0x14);
}
