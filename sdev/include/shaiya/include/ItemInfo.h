#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemType.h>

namespace shaiya
{
    enum struct ItemCooldown : ULONG
    {
        // ReqIg
        Value0 = 0,        // 0x581D84
        Value1 = 15000,    // 0x581D88
        Value2 = 20000,    // 0x581D8C
        Value3 = 25000,    // 0x581D90
        Value4 = 30000,    // 0x581D94
        Value5 = 60000,    // 0x581D98
        Value6 = 120000,   // 0x581D9C
        Value7 = 0,        // 0x581DA0
        Value8 = 0,        // 0x581DA4
        Value9 = 0,        // 0x581DA8
        Value10 = 600000,  // 0x581DAC
        Value11 = 2000     // 0x581DB0
    };

    enum struct RealType : UINT32
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
        Teleportation,
        Quest
    };

    enum struct MarketType : UINT8
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
        //Vehicle, // 6.4 PT
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
        enum struct 
            ReqOg : UINT8
        {
            Tradable,
            AccountBound,
            CharacterBound
        } reqOg;                    //0x31
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
