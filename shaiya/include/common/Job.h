#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct Job : uint8_t
    {
        AttackFighter,
        DefenseFighter,
        PatrolRogue,
        ShootRogue,
        AttackMage,
        DefenseMage
    };
}
