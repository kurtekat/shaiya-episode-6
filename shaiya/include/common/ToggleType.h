#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ToggleType : uint8_t
    {
        Triggered = 1,
        Unknown,
        Stopped
    };
}
