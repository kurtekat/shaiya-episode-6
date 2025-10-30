#pragma once
#include <shaiya/include/common.h>
#include "DamageMob.h"
#include "SSyncList.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDamageMob
    {
        bool fairAttack;
        PAD(3);
        SSyncList<DamageMob> list;
        // 0x30
    };
    #pragma pack(pop)

    static_assert(sizeof(CDamageMob) == 0x30);
}
