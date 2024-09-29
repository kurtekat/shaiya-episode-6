#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ShapeType : uint8_t
    {
        None,
        Chicken = 4,
        Dog,
        Horse,
        Pig,
        Fox = 10,
        Wolf,
        Knight,
        Stealth,
        Disguise = 100,
        Degeneration,
        Transformation,
    };
}
