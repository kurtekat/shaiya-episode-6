#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CTextureList
    {
        PAD(16);
        int32_t count;  //0x10
        PAD(4);
        // 0x18
    };
    #pragma pack(pop)

    static_assert(sizeof(CTextureList) == 0x18);
}
