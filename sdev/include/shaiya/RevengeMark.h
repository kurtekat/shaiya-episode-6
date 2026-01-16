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
        static void send(CUser* user, unsigned charId, unsigned killCount);
    };
    #pragma pack(pop)

    inline std::map<CharId, std::map<CharId, uint32_t/*KillCount*/>> g_revengeMarks{};
}
