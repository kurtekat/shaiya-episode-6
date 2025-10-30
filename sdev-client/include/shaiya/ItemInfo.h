#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    enum struct ExtDuration : uint8_t
    {
        None,
        Unexpandable,
        Expandable
    };

    // notes: item types
    enum struct RealType : uint8_t
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
        Helmet,
        UpperArmor,
        LowerArmor,
        Shield,
        Gloves,
        Boots,
        Ring,
        Necklace,
        Cloak,
        Bracelet,
        Consumable,
        // 27, 99
        Quest,
        // 30, 98
        Lapis = 30,
        FuryHelmet,
        FuryUpperArmor,
        FuryLowerArmor,
        FuryShield,
        FuryGloves,
        FuryBoots,
        FuryCloak,
        Bracelet2,
        // 100, 101, 102, 103
        Other = 100,
        Wings = 121
    };

    #pragma pack(push, 1)
    struct ItemInfo
    {
        char* name;               //0x00
        char* description;        //0x04
        uint8_t type;             //0x08
        uint8_t typeId;           //0x09
        uint8_t model;            //0x0A
        uint8_t icon;             //0x0B
        uint16_t level;           //0x0C
        Faction country;          //0x0E
        bool fighter;             //0x0F
        bool defender;            //0x10
        bool ranger;              //0x11
        bool archer;              //0x12
        bool mage;                //0x13
        bool priest;              //0x14
        Grow grow;                //0x15
        uint16_t reqStr;          //0x16
        uint16_t reqDex;          //0x18
        uint16_t reqRec;          //0x1A
        uint16_t reqInt;          //0x1C
        uint16_t reqWis;          //0x1E
        int32_t reqLuc;           //0x20
        int16_t reqVg;            //0x24
        ReqOg reqOg;              //0x26
        uint8_t reqIg;            //0x27
        uint16_t range;           //0x28
        uint8_t attackTime;       //0x2A
        Attribute attribute;      //0x2B
        ItemEffect effect;        //0x2C
        uint8_t slots;            //0x2D
        uint16_t quality;         //0x2E
        uint16_t minAtkPower;     //0x30
        uint16_t addAtkPower;     //0x32
        uint16_t defense;         //0x34
        uint16_t resistance;      //0x36
        uint16_t health;          //0x38
        uint16_t stamina;         //0x3A
        uint16_t mana;            //0x3C
        uint16_t strength;        //0x3E
        uint16_t dexterity;       //0x40
        uint16_t reaction;        //0x42
        uint16_t intelligence;    //0x44
        uint16_t wisdom;          //0x46
        uint16_t luck;            //0x48
        PAD(2);
        uint32_t buy;             //0x4C
        uint32_t sell;            //0x50
        uint32_t dropGrade;       //0x54
        uint8_t craftExpansions;  //0x58
        uint8_t count;            //0x59
        PAD(2);
        uint32_t duration;        //0x5C
        ExtDuration extDuration;  //0x60
        PAD(47);
        uint8_t vehicleModel;     //0x90
        PAD(3);
        uint8_t vehicleSeats;     //0x94
        PAD(3);
        uint32_t vehicleSpeed;    //0x98
        bool isSnowboard;         //0x9C
        PAD(15);
        // 0xAC
    };
    #pragma pack(pop)

    static_assert(sizeof(ItemInfo) == 0xAC);
}
