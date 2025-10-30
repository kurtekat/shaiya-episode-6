#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ChatType : int32_t
    {
        Damage15 = 15,   // Orange
        Damage16,        // Red
        Damage20 = 20,   // Pink
        Death = 17,      // Red
        Acquire18,       // Yellow
        Acquire19,       // Green
        Acquire21 = 21,  // Blue
        Acquire22,       // Yellow
        Acquire31 = 31,  // White
        Notice23 = 23,   // White
        Notice24,        // Yellow
        Notice25,        // White
        Notice26,        // White (Chat)
        Notice27,        // White (Chat)
        Notice28,        // White
        Notice29,        // White
        Notice30,        // White
        Notice50 = 50,   // White
        Chat32 = 32,     // White
        Chat33,          // White
        ChatNormal,
        ChatParty,
        ChatWhisper,
        ChatGuild,
        ChatTrade,
        ChatShout,
        Chat40,          // Yellow
        ChatAdmin,
        ChatWarning,
        Chat43,          // White
        Chat44,          // White
        Chat45,          // Red
        Chat46,          // Pink
        ChatAll,
        ChatZone,
        ChatRaid
    };
}
