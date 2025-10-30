#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // 0057CD30 ctor
    struct CEffectModel
    {
        PAD(16);
        String<16> fileName;  //0x10
        // 0x20
        PAD(20);
        // 0x34
    };
    #pragma pack(pop)

    static_assert(sizeof(CEffectModel) == 0x34);
}
