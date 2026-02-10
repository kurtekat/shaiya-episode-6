#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct AuthStatus : uint8_t
    {
        AdminA = 1, // 16
        AdminB,     // 32
        AdminC,     // 48
        AdminD,     // 64
        AdminE,     // 80
        None = 11
    };
}
