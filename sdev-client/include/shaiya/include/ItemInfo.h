#pragma once
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemType.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    // notes: item types
    enum struct RealType : UINT8
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
        FuryShoes,
        FuryCloak,
        Bracelet2,
        // 100, 101, 102, 103
        Special = 100,
        Wings = 121
    };
    
    #pragma pack(push, 1)
    struct ItemInfo
    {
        char* name;               //0x00
        char* desc;               //0x04
        UINT8 type;               //0x08
        UINT8 typeId;             //0x09
        UINT8 model;              //0x0A
        UINT8 icon;               //0x0B
        UINT16 reqLevel;          //0x0C
        Faction country;          //0x0E
        bool attackFighter;       //0x0F
        bool defenseFighter;      //0x10
        bool patrolRogue;         //0x11
        bool shootRogue;          //0x12
        bool attackMage;          //0x13
        bool defenseMage;;        //0x14
        Grow grow;                //0x15
        UINT16 reqStr;            //0x16
        UINT16 reqDex;            //0x18
        UINT16 reqRec;            //0x1A
        UINT16 reqInt;            //0x1C
        UINT16 reqWis;            //0x1E
        INT32 reqLuc;             //0x20
        INT16 reqVg;              //0x24
        enum struct 
            ReqOg : UINT8 {
            Tradable,
            AccountBound,
            CharacterBound
        } reqOg;                  //0x26
        UINT8 reqIg;              //0x27
        UINT16 range;             //0x28
        UINT8 attackTime;         //0x2A
        Attribute attribute;      //0x2B
        ItemEffect effect;        //0x2C
        UINT8 slotCount;          //0x2D
        UINT16 quality;           //0x2E
        UINT16 minAtkPower;       //0x30
        UINT16 addAtkPower;       //0x32
        UINT16 defense;           //0x34
        UINT16 resistance;        //0x36
        UINT16 health;            //0x38
        UINT16 stamina;           //0x3A
        UINT16 mana;              //0x3C
        UINT16 strength;          //0x3E
        UINT16 dexterity;         //0x40
        UINT16 reaction;          //0x42
        UINT16 intelligence;      //0x44
        UINT16 wisdom;            //0x46
        UINT16 luck;              //0x48
        PAD(2);
        UINT32 buy;               //0x4C
        UINT32 sell;              //0x50
        UINT32 dropGrade;         //0x54
        UINT8 composeCount;       //0x58
        UINT8 count;              //0x59
        PAD(2);
        UINT32 duration;          //0x5C
        enum struct 
            ExtDuration : UINT8 {
            None,
            Unexpandable,
            Expandable
        } extDuration;            //0x60
        PAD(47);
        UINT8 vehicleModel;       //0x90
        PAD(3);
        UINT8 vehicleSeats;       //0x94
        PAD(3);
        UINT32 vehicleSpeed;      //0x98
        bool isSnowboard;         //0x9C
        PAD(15);
        // 0xAC
    };
    #pragma pack(pop)

    static_assert(sizeof(ItemInfo) == 0xAC);
}
