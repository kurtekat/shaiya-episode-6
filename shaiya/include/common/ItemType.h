#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct ItemType : uint8_t
    {
        OneHandedSword = 1,
        TwoHandedSword,
        OneHandedAxe,
        TwoHandedAxe,
        DualWeapon,
        Spear,
        OneHandedBlunt,
        TwoHandedBlunt,
        ReverseDagger,
        Dagger,
        Javelin,
        Staff,
        Bow,
        Crossbow,
        Knuckles,
        LightHelmet,
        LightUpperArmor,
        LightLowerArmor,
        LightShield,
        LightGloves,
        LightBoots,
        Ring,
        Necklace,
        LightCloak,
        Consumable25,
        Gold,
        Quest27,
        Quest28,
        Quest29,
        Lapis,
        FuryHelmet,
        FuryUpperArmor,
        FuryLowerArmor,
        FuryShield,
        FuryGloves,
        FuryBoots,
        Ring2,
        Consumable38,
        FuryCloak,
        Bracelet,
        Consumable41,
        Vehicle,
        Etin,
        Consumable44,
        OneHandedSword2,
        TwoHandedSword2,
        OneHandedAxe2,
        TwoHandedAxe2,
        DualWeapon2,
        DualWeapon3,
        Spear2,
        Spear3,
        OneHandedBlunt2,
        OneHandedBlunt3,
        TwoHandedBlunt2,
        TwoHandedBlunt3,
        ReverseDagger2,
        Dagger2,
        Javelin2,
        Staff2,
        Staff3,
        Bow2,
        Bow3,
        Crossbow2,
        Knuckles2,
        LightHelmet2,
        LightUpperArmor2,
        LightLowerArmor2,
        LightShield2,
        LightGloves2,
        LightBoots2,
        LightHelmet3,
        LightUpperArmor3,
        LightLowerArmor3,
        LightShield3,
        LightGloves3,
        LightBoots3,
        Consumable78,
        Consumable79,
        Consumable80,
        FuryHelmet2,
        FuryUpperArmor2,
        FuryLowerArmor2,
        FuryShield2,
        FuryGloves2,
        FuryBoots2,
        FuryHelmet3,
        FuryUpperArmor3,
        FuryLowerArmor3,
        FuryShield3,
        FuryGloves3,
        FuryBoots3,
        Unknown93,
        GoldBar,
        Lapisian,
        Necklace2,
        Bracelet2,
        Lapis98,
        Quest99,
        Other100,
        Other101,
        Other102,
        Other103,
        Pet = 120,
        Wings,
        Costume = 150
    };

    inline bool operator==(ItemType lhs, int rhs)
    {
        return static_cast<int>(lhs) == rhs;
    }

    inline bool operator==(int lhs, ItemType rhs)
    {
        return lhs == static_cast<int>(rhs);
    }

    inline bool operator!=(ItemType lhs, int rhs)
    {
        return static_cast<int>(lhs) != rhs;
    }

    inline bool operator!=(int lhs, ItemType rhs)
    {
        return lhs != static_cast<int>(rhs);
    }
}
