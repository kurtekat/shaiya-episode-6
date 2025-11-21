#pragma once
#include <cstdint>

namespace shaiya
{
    constexpr int ItemSlotCount = 24;

    struct ItemSlot
    {
        enum
        {
            Helmet,
            UpperArmor,
            LowerArmor,
            Gloves,
            Boots,
            Weapon,
            Shield,
            Cloak,
            Necklace,
            Ring1,
            Ring2,
            Bracelet1,
            Bracelet2,
            Vehicle,
            Pet,
            Costume,
            Wings
        };
    };
}
