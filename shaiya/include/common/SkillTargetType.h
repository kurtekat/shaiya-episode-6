#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct SkillTargetType : uint8_t
    {
        None,
        Trap,
        Caster,
        Target,
        AlliesNearCaster,
        Allies,
        EnemiesNearCaster,
        EnemiesNearTarget
    };
}
