#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct NeedWeapon
    {
        bool oneHandedSword;
        bool twoHandedSword;
        bool oneHandedAxe;
        bool twoHandedAxe;
        bool dualWeapon;
        bool spear;
        bool oneHandedBlunt;
        bool twoHandedBlunt;
        bool reverseDagger;
        bool dagger;
        bool javelin;
        bool staff;
        bool bow;
        bool crossbow;
        bool knuckles;
        bool shield;
    };
    #pragma pack(pop)
}
