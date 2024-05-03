#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    template<class T>
    struct CVector
    {
        PAD(24);
    };

    static_assert(sizeof(CVector<void*>) == 0x18);
}
