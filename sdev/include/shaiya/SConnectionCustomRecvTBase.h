#pragma once
#include <shaiya/include/common.h>
#include "SConnectionCustomRecv.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionCustomRecvTBase : SConnectionCustomRecv
    {
        int type;  //0xD0
        PAD(4);
        // 0xD8
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionCustomRecvTBase) == 0xD8);
}
