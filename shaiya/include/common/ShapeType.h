#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct ShapeType : UINT8
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
