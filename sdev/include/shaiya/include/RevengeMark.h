#pragma once
#include <map>
#include <vector>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RevengeMark
    {
        uint32_t killerId;
        uint32_t killCount;

        /// <summary>
        /// The max kill count defined in the client.
        /// </summary>
        constexpr static uint32_t maxKillCount = 999;
    };
    #pragma pack(pop)

    inline std::map<CharId, std::vector<RevengeMark>> g_revengeMark;
}
