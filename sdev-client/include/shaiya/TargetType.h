#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct TargetType : int32_t
    {
        Default = -1,
        Mob,
        Item,
        User,
        Npc
    };
}
