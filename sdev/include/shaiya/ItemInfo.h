#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemEffect.h>

namespace shaiya
{
    inline constexpr int ItemCraft_MAX = 99;   // ReqWis
    inline constexpr int ItemGrade_MAX = 3072;

    inline constexpr int ItemId_MIN = 1 * 1000 + 1;
    inline constexpr int ItemId_MAX = UINT8_MAX * 1000 + UINT8_MAX;

    // notes: item types
    enum struct RealType : int32_t
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
        Boots,
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
    enum struct MarketType : uint8_t
    {
        All,
        // 2,4,46,48
        TwoHandedWeapon,
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
        Boots,
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
        Other,
        // ?
        Max
    };

    enum struct ReqOg : uint8_t
    {
        Tradable,
        AccountBound,
        CharacterBound
    };

    #pragma pack(push, 1)
    struct ItemInfo
    {
        uint32_t itemId;            //0x00
        String<32> itemName;        //0x04
        uint8_t type;               //0x24
        uint8_t typeId;             //0x25
        Faction country;            //0x26
        bool fighter;               //0x27
        bool defender;              //0x28
        bool ranger;                //0x29
        bool archer;                //0x2A
        bool mage;                  //0x2B
        bool priest;                //0x2C
        PAD(1);
        uint16_t level;             //0x2E
        Grow grow;                  //0x30
        ReqOg reqOg;                //0x31
        uint8_t reqIg;              //0x32
        PAD(1);
        uint16_t reqVg;             //0x34
        uint16_t reqStr;            //0x36
        uint16_t reqDex;            //0x38
        uint16_t reqRec;            //0x3A
        uint16_t reqInt;            //0x3C
        uint16_t reqWis;            //0x3E
        uint16_t reqLuc;            //0x40
        uint16_t range;             //0x42
        uint8_t attackTime;         //0x44
        Attribute attribute;        //0x45
        ItemEffect effect;          //0x46
        uint8_t slots;              //0x47
        uint8_t speed;              //0x48
        uint8_t exp;                //0x49
        uint8_t craftExpansions;    //0x4A
        uint8_t count;              //0x4B
        uint16_t maxQuality;        //0x4C
        uint16_t midQuality;        //0x4E
        uint16_t lowQuality;        //0x50
        uint16_t maxAtkPower;       //0x52
        uint16_t maxAtkPowerMidQ;   //0x54
        uint16_t maxAtkPowerLowQ;   //0x56
        uint16_t minAtkPower;       //0x58
        uint16_t minAtkPowerMidQ;   //0x5A
        uint16_t minAtkPowerLowQ;   //0x5C
        uint16_t defense;           //0x5E
        uint16_t defenseMidQ;       //0x60
        uint16_t defenseLowQ;       //0x62
        uint16_t resistance;        //0x64
        uint16_t resistanceMidQ;    //0x66
        uint16_t resistanceLowQ;    //0x68
        uint16_t health;            //0x6A
        uint16_t stamina;           //0x6C
        uint16_t mana;              //0x6E
        uint16_t strength;          //0x70
        uint16_t dexterity;         //0x72
        uint16_t reaction;          //0x74
        uint16_t intelligence;      //0x76
        uint16_t wisdom;            //0x78
        uint16_t luck;              //0x7A
        uint16_t dropGrade;         //0x7C
        uint16_t dropLimit;         //0x7E
        uint32_t buy;               //0x80
        uint32_t sell;              //0x84
        PAD(4);
        int32_t dropCount;          //0x8C
        uint32_t dropDelay;         //0x90
        uint32_t dropRandom;        //0x94
        tick32_t nextDropTime;      //0x98
        bool questStart;            //0x9C
        PAD(3);
        RealType realType;          //0xA0
        MarketType marketType;      //0xA4
        PAD(3);
        // 0xA8
    };
    #pragma pack(pop)

    static_assert(sizeof(ItemInfo) == 0xA8);
}
