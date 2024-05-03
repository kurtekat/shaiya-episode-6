#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    // users
    enum struct Country : UINT8
    {
        Light,
        Fury,
        Neutral
    };

    // mobs, npcs, portals
    enum struct Country2 : UINT32
    {
        Neutral,
        Light,
        Fury
    };

    // items, skills
    enum struct Country3 : UINT8
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
