#pragma once
#include <shaiya/include/common.h>
#include "GateLink.h"
#include "Npc.h"

namespace shaiya
{
    inline constexpr int NpcGateCount = 3;
    using NpcGates = Array<GateLink, NpcGateCount>;

    #pragma pack(push, 1)
    struct NpcGateKeeper : Npc
    {
        NpcGates gates;  //0x124
        // 0x460
    };
    #pragma pack(pop)

    static_assert(sizeof(NpcGateKeeper) == 0x460);
}
