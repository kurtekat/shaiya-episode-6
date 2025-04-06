#pragma once
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    class RevengeMark
    {
    public:

        uint32_t charId;
        uint32_t killCount;

        static void send(CUser* user, uint charId, uint killCount);

        /// <summary>
        /// The max kill count defined in the client.
        /// </summary>
        static constexpr uint32_t maxKillCount = 999;
    };
    #pragma pack(pop)

    inline std::map<uint32_t, std::vector<RevengeMark>> g_revengeMarks;
}
