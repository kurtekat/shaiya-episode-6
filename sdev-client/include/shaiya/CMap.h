#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    template<class K, class V>
    struct CMap
    {
        PAD(12);
        int32_t count;  //0x0C
        PAD(4);
        // 0x14
    };
    #pragma pack(pop)

    static_assert(sizeof(CMap<uint32_t, void>) == 0x14);
}
