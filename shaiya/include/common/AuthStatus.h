#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct AuthStatus : uint8_t
    {
        AdminA = 1,
        AdminB,
        AdminC,
        AdminD,
        AdminE,
        None = 11
    };
}
