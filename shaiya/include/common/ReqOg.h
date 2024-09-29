#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ReqOg : uint8_t
    {
        Tradable,
        AccountBound,
        CharacterBound
    };
}
