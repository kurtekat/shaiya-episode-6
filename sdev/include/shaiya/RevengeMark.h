#pragma once
#include <cstdint>
#include <map>

namespace shaiya
{
    struct CUser;

    struct RevengeMarkConstants
    {
        /// <summary>
        /// The max kill count defined in the client.
        /// </summary>
        static constexpr uint32_t MaxKillCount = 999;
    };

    #pragma pack(push, 1)
    class RevengeMark
    {
    public:

        /// <summary>
        /// Sends packet 0x229 to the user.
        /// </summary>
        static void send(CUser* user, unsigned charId, unsigned killCount);
    };
    #pragma pack(pop)

    inline std::map<uint32_t/*CharID*/, std::map<uint32_t/*CharID*/, uint32_t/*KillCount*/>> g_revengeMarks{};
}
