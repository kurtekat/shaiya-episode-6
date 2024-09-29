#pragma once
#include <cstdint>

namespace shaiya
{
    // users
    enum struct Country : uint8_t
    {
        Light,
        Fury,
        Neutral
    };

    // mobs, npcs, portals
    enum struct Country2 : uint32_t
    {
        Neutral,
        Light,
        Fury
    };

    // items, skills
    enum struct Country3 : uint8_t
    {
        Human,
        Elf,
        Light,
        DeathEater,
        Vail,
        Fury,
        Neutral
    };
}
