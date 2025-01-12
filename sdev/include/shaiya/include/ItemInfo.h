#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    // notes: item types
    enum struct RealType : UINT32
    {
        // 1,45
        OneHandedSword = 1,
        // 2,46
        TwoHandedSword,
        // 3,47
        OneHandedAxe,
        // 4,48
        TwoHandedAxe,
        // 5,49,50
        DualWeapon,
        // 6,51,52
        Spear,
        // 7,53,54
        OneHandedBlunt,
        // 8,55,56
        TwoHandedBlunt,
        // 9,57
        ReverseDagger,
        // 10,58
        Dagger,
        // 11,59
        Javelin,
        // 12,60,61
        Staff,
        // 13,62,63
        Bow,
        // 14,64
        Crossbow,
        // 15,65
        Knuckles,
        // 16,31,66,72,81,87
        Helmet,
        // 17,32,67,73,82,88
        UpperArmor,
        // 18,33,68,74,83,89
        LowerArmor,
        // 19,34,69,75,84,90
        Shield,
        // 20,35,70,76,85,91
        Gloves,
        // 21,36,71,77,86,92
        Shoes,
        // 22,37
        Ring,
        // 23,96
        Necklace,
        // 24,39
        Cloak,
        // 40,97
        Bracelet,
        // 25,44,100,38,41,101,102,103
        Consumable,
        // 27,28,29,99
        Quest,
        // 30,95
        Upgrade
    };

    // notes: item types
    enum struct MarketType : UINT8
    {
        // 2,4,46,48
        TwoHandedWeapon = 1,
        // 1,3,45,47
        OneHandedWeapon,
        // 5,49,50
        DualWeapon,
        // 6,51,52
        Spear,
        // 7,8,53,54,55,56
        HeavyWeapon,
        // 9,15,57,65
        Knuckles,
        // 10,58
        Dagger,
        // 12,60,61
        Staff,
        // 13,62,63
        Bow,
        // 11,14,59,64
        Projectile,
        // 16,31,66,72,81,87
        Helmet,
        // 17,32,67,73,82,88
        UpperArmor,
        // 18,33,68,74,83,89
        LowerArmor,
        // 20,35,70,76,85,91
        Gloves,
        // 21,36,71,77,86,92
        Shoes,
        // 24,39
        Cloak,
        // 19,34,69,75,84,90
        Shield,
        // 23,96
        Necklace,
        // 22,37
        Ring,
        // 40,97
        Bracelet,
        // 30
        Lapis,
        // 95
        Lapisian,
        // 25,44,38,41
        Consumable,
        // 42
        Mount,
        // 100,101,102,103
        Special
    };

    #pragma pack(push, 1)
    struct ItemInfo
    {
        UINT32 itemId;              //0x00
        CharArray<32> itemName;     //0x04
        UINT8 type;                 //0x24
        UINT8 typeId;               //0x25
        Faction country;            //0x26
        bool attackFighter;         //0x27
        bool defenseFighter;        //0x28
        bool patrolRogue;           //0x29
        bool shootRogue;            //0x2A
        bool attackMage;            //0x2B
        bool defenseMage;;          //0x2C
        PAD(1);
        UINT16 reqLevel;            //0x2E
        Grow grow;                  //0x30
        ReqOg reqOg;                //0x31
        UINT8 reqIg;                //0x32
        PAD(1);
        UINT16 reqVg;               //0x34
        UINT16 reqStr;              //0x36
        UINT16 reqDex;              //0x38
        UINT16 reqRec;              //0x3A
        UINT16 reqInt;              //0x3C
        UINT16 reqWis;              //0x3E
        UINT16 reqLuc;              //0x40
        UINT16 range;               //0x42
        UINT8 attackTime;           //0x44
        Attribute attribute;        //0x45
        ItemEffect effect;          //0x46
        UINT8 slotCount;            //0x47
        UINT8 speed;                //0x48
        UINT8 exp;                  //0x49
        UINT8 composeCount;         //0x4A
        UINT8 count;                //0x4B
        UINT16 maxQuality;          //0x4C
        UINT16 midQuality;          //0x4E
        UINT16 lowQuality;          //0x50
        UINT16 maxAtkPower;         //0x52
        UINT16 maxAtkPowerMidQ;     //0x54
        UINT16 maxAtkPowerLowQ;     //0x56
        UINT16 minAtkPower;         //0x58
        UINT16 minAtkPowerMidQ;     //0x5A
        UINT16 minAtkPowerLowQ;     //0x5C
        UINT16 defense;             //0x5E
        UINT16 defenseMidQ;         //0x60
        UINT16 defenseLowQ;         //0x62
        UINT16 resistance;          //0x64
        UINT16 resistanceMidQ;      //0x66
        UINT16 resistanceLowQ;      //0x68
        UINT16 health;              //0x6A
        UINT16 stamina;             //0x6C
        UINT16 mana;                //0x6E
        UINT16 strength;            //0x70
        UINT16 dexterity;           //0x72
        UINT16 reaction;            //0x74
        UINT16 intelligence;        //0x76
        UINT16 wisdom;              //0x78
        UINT16 luck;                //0x7A
        // max: 3072
        UINT16 itemDropGrade;       //0x7C
        UINT16 itemDropLimit;       //0x7E
        UINT32 buy;                 //0x80
        UINT32 sell;                //0x84
        PAD(4);
        UINT32 itemDropCount;       //0x8C
        PAD(4);
        UINT32 itemDropDelay;       //0x94
        DWORD itemDropEnableTick;   //0x98
        PAD(4);
        RealType realType;          //0xA0
        MarketType marketType;      //0xA4
        PAD(3);
        // 0xA8
    };
    #pragma pack(pop)

    static_assert(sizeof(ItemInfo) == 0xA8);
}
