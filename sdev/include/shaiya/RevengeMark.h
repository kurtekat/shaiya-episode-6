#pragma once
#include <cstdint>
#include <map>

namespace shaiya
{
    using CharId = uint32_t;

    struct CUser;

    #pragma pack(push, 1)
    class RevengeMark
    {
    public:

        /// <summary>
        /// Sends packet 0x229 to the user.
        /// </summary>
        static void SendKillCount(CUser* user, unsigned killerId, unsigned killCount);
        static void SendRevengeSuccess(CUser* user, unsigned targetId);
    };
    #pragma pack(pop)

    inline std::map<CharId, std::map<CharId, unsigned/*KillCount*/>> g_revengeMarks{};
}
