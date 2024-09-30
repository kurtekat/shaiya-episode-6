#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct SkillDebuffType : uint8_t
    {
        None,
        Sleep,
        Unconscious,
        Silence,
        Darkness,
        Pause,
        Slow,
        Dying,
        Death,
        Poison,
        Illness,
        Delusion,
        Doom,
        Fear,
        Dull,
        Misfortune
    };
}
