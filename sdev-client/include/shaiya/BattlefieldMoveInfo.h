#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BattlefieldMoveInfo
    {
        int32_t mapId;
        int32_t levelMin;
        int32_t levelMax;
    };
    #pragma pack(pop)

    struct BattlefieldLvInRangeF
    {
        explicit BattlefieldLvInRangeF(int level)
            : m_level(level)
        {
        }

        bool operator()(const BattlefieldMoveInfo& info)
        {
            return m_level >= info.levelMin
                && m_level <= info.levelMax;
        }

    private:

        int m_level;
    };

    inline std::vector<BattlefieldMoveInfo> g_pvpMoveData{};
}
