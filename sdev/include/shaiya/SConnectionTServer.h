#pragma once
#include <shaiya/include/common.h>
#include "SConnectionCustomRecvTBase.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SConnectionTServer : SConnectionCustomRecvTBase
    {
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionTServer) == 0xD8);
}
