#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    template<class K, class V>
    struct CMap
    {
        PAD(12);
        UINT32 count;  //0x0C
        PAD(4);
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(CMap<ULONG, void*>) == 0x14);
}
