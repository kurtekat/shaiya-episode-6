#pragma once
#define SHAIYA_EP6_4_PT

#include <array>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
#ifdef SHAIYA_EP6_4_PT
    constexpr int max_equipment_slot = 17;
#else
    constexpr int max_equipment_slot = 8;
#endif

    constexpr int warehouse_bag = 100;
    constexpr int bank_bag = 200;
    constexpr int guild_warehouse_bag = 255;

    constexpr int max_inventory_bag = 6;
    constexpr int max_inventory_slot = 24;
    constexpr int max_warehouse_slot = 240;
    constexpr int min_warehouse_slot = 120;

    template<class T, size_t N>
    using Array = std::array<T, N>;

    template<size_t N>
    using CharArray = std::array<char, N>;

    using Address = unsigned;
    using Packet = unsigned char*;

    enum EquipmentSlot
    {
        Helmet,      //0x1C0
        UpperArmor,  //0x1C4
        LowerArmor,  //0x1C8
        Gloves,      //0x1CC
        Shoes,       //0x1D0
        Weapon,      //0x1D4
        Shield,      //0x1D8
        Cloak,       //0x1DC
        Ring1,       //0x1E0
        Ring2,       //0x1E4
        Bracelet1,   //0x1E8
        Bracelet2,   //0x1EC
        Necklace,    //0x1F0
        Vehicle,     //0x1F4
        Pet,         //0x1F8
        Costume,     //0x1FC
        Wings,       //0x200
        Index17,     //0x204
        Index18,     //0x208
        Index19,     //0x20C
        Index20,     //0x210
        Index21,     //0x214
        Index22,     //0x218
        Index23      //0x21C
        // 0x220
    };
}
