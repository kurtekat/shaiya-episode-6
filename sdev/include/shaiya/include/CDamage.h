#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/Damage.h"
#include "include/shaiya/include/SSyncList.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDamage
    {
        SSyncList<Damage> list;
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(CDamage) == 0x2C);
}
