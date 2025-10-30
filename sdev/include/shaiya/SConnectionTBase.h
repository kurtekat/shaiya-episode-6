#pragma once
#include <shaiya/include/common.h>
#include "SConnection.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionTBase : SConnection
    {
        int type;  //0xD0
        PAD(4);
        // 0xD8
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionTBase) == 0xD8);
}
