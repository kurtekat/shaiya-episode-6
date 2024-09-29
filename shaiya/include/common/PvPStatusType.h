#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct PvPStatusType : uint8_t
    {
        Kill,   // K1
        Death,  // K2
        Win,    // K3
        Loss    // K4
    };
}
