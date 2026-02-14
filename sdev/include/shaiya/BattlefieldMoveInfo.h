#pragma once
#include <array>
#include <cstdint>
#include <map>
#include "MapPos.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct BattlefieldMoveInfo
    {
        int32_t levelMin;
        int32_t levelMax;
        std::array<MapPos, 4> mapPos;
    };
    #pragma pack(pop)

    inline std::map<int32_t/*MapID*/, BattlefieldMoveInfo> g_pvpMoveData{};
}
