#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    template<class Key, class Value>
    struct CMap
    {
        PAD(44);
        // 0x2C
    };

    static_assert(sizeof(CMap<void, void>) == 0x2C);
}
