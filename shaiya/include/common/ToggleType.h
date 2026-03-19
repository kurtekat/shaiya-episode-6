#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ToggleType : uint8_t
    {
        Triggered = 1,
        Stopped = 3,
        NotEnoughHP = 5,
        NotEnoughSP,
        NotEnoughMP
    };
}
