#pragma once
#include <map>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    class RevengeMark
    {
    public:

        /// <summary>
        /// Sends packet 0x229 to the user.
        /// </summary>
        static void send(CUser* user, uint charId, uint killCount);

        /// <summary>
        /// The max kill count defined in the client.
        /// </summary>
        static constexpr uint32_t maxKillCount = 999;
    };
    #pragma pack(pop)

    inline std::map<uint32_t/*CharID*/, std::map<uint32_t/*CharID*/, uint32_t/*KillCount*/>> g_revengeMarks;
}
