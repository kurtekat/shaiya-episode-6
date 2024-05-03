#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct SkillTargetType : UINT8
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
