#pragma once
#include <cstdint>
#include <map>

namespace shaiya
{
    using CharId = uint32_t;

    struct CUser;

    struct RevengeMark
    {
        static void SendKillCount(CUser* user, unsigned killerId, unsigned killCount);
        static void SendRevengeSuccess(CUser* user, unsigned targetId);
    };

    inline std::map<CharId, std::map<CharId, unsigned/*KillCount*/>> g_revengeMarks{};
}
