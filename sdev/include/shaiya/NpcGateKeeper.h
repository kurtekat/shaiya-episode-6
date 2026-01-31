#pragma once
#include <shaiya/include/common.h>
#include "GateLink.h"
#include "Npc.h"

namespace shaiya
{
    using NpcGates = Array<GateLink, 3>;

    #pragma pack(push, 1)
    struct NpcGateKeeper : Npc
    {
        NpcGates gates;  //0x124
        // 0x460
    };
    #pragma pack(pop)

    static_assert(sizeof(NpcGateKeeper) == 0x460);
}
