#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    template<class K, class V>
    struct CMap
    {
        PAD(12);
        UINT32 count;  //0x0C
        PAD(4);
        // 0x14
    };

    static_assert(sizeof(CMap<ULONG, void*>) == 0x14);
}
