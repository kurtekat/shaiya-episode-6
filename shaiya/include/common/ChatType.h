#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ChatType : uint8_t
    {
        Normal = 1,
        To,
        Guild,
        Party,
        Trade = 5,
        All = 5,
        Shout,
        Zone
    };
}
