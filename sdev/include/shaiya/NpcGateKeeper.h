#pragma once
#include <shaiya/include/common.h>
#include "GateLink.h"
#include "Npc.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct NpcGateKeeper : Npc
    {
        // 0x124
        Array<GateLink, 3> gates;
        // 0x460
    };
    #pragma pack(pop)

    static_assert(sizeof(NpcGateKeeper) == 0x460);
}
