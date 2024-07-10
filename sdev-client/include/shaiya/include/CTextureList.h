#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CTextureList
    {
        PAD(16);
        UINT32 count;  //0x10
        PAD(4);
        // 0x18
    };
    #pragma pack(pop)
}
