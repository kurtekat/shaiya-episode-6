#pragma once
#include <array>

namespace shaiya
{
    enum struct EquipmentSlot : uint8_t
    {
        Helmet,      //0x1C0
        UpperArmor,  //0x1C4
        LowerArmor,  //0x1C8
        Gloves,      //0x1CC
        Shoes,       //0x1D0
        Weapon,      //0x1D4
        Shield,      //0x1D8
        Cloak,       //0x1DC
        Necklace,    //0x1E0
        Ring1,       //0x1E4
        Ring2,       //0x1E8
        Bracelet1,   //0x1EC
        Bracelet2,   //0x1F0
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

    #pragma pack(push, 1)
    template<size_t N>
    struct Equipment
    {
        std::array<uint8_t, N> type;
        std::array<uint8_t, N> typeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ShapeItem
    {
        uint8_t type;
        uint8_t typeId;
        uint8_t enchantStep;
    };
    #pragma pack(pop)

    template<size_t N>
    using ShapeEquipment = std::array<ShapeItem, N>;
}
