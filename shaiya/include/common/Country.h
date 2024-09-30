#pragma once
#include <cstdint>

namespace shaiya
{
    // mobs, npcs, users
    enum struct Country : uint8_t
    {
        Light,
        Fury,
        Neutral
    };

    enum struct Faction : uint8_t
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
