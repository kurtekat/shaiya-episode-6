#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CEffectModelList
    {
        PAD(16);
        int32_t count;  //0x10
        PAD(4);
        // 0x18
    };
    #pragma pack(pop)

    static_assert(sizeof(CEffectModelList) == 0x18);
}
