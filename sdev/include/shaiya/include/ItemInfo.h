#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/item/ExtDuration.h>
#include <shaiya/include/item/ItemEffect.h>
#include <shaiya/include/item/ItemType.h>
#include <shaiya/include/item/ReqOg.h>

namespace shaiya
{
    using ItemName = std::array<char, 32>;

    enum ItemCooldown
    {
        ReqIg_0 = 0,        // 0x581D84
        ReqIg_1 = 15000,    // 0x581D88
        ReqIg_2 = 20000,    // 0x581D8C
        ReqIg_3 = 25000,    // 0x581D90
        ReqIg_4 = 30000,    // 0x581D94
        ReqIg_5 = 60000,    // 0x581D98
        ReqIg_6 = 120000,   // 0x581D9C
        ReqIg_7 = 0,        // 0x581DA0
        ReqIg_8 = 0,        // 0x581DA4
        ReqIg_9 = 0,        // 0x581DA8
        ReqIg_10 = 600000,  // 0x581DAC
        ReqIg_11 = 2000     // 0x581DB0
    };

    enum struct ItemRealType : UINT32
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
        Shoes,
        Ring,
        Necklace,
        Cloak,
        Bracelet,
        Teleportation
    };

    enum struct ItemMarketType : UINT8
    {
        TwoHandedWeapon = 1,
        OneHandedWeapon,
        DualWeapon,
        Spear,
        HeavyWeapon,
        Knuckles,
        Dagger,
        Staff,
        Bow,
        Projectile,
        Helmet,
        UpperArmor,
        LowerArmor,
        Gloves,
        Shoes,
        Cloak,
        Shield,
        Necklace,
#ifdef SHAIYA_EP6_4_PT
        Vehicle,
#endif
        Ring,
        Bracelet,
        Lapis,
        Lapisian,
        Other,
        Mount,
        HighQuality
    };

    #pragma pack(push, 1)
    struct ItemInfo
    {
        UINT32 itemId;              //0x00
        ItemName itemName;          //0x04
        UINT8 type;                 //0x24
        UINT8 typeId;               //0x25
        Country3 country;           //0x26
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
        UINT32 dropGrade;           //0x7C
        UINT32 buy;                 //0x80
        UINT32 sell;                //0x84
        // custom
        UINT32 duration;            //0x88
        ExtDuration extDuration;    //0x8C
        PAD(19);
        ItemRealType realType;      //0xA0
        ItemMarketType marketType;  //0xA4
        PAD(3);
        // 0xA8
    };
    #pragma pack(pop)
}
