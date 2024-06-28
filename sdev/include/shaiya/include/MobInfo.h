#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>

namespace shaiya
{
    using MobResistSkill = Array<UINT8, 6>;
    using MobResistState = Array<bool, 15>;

    enum struct MobCooldown : ULONG
    {
        AttackSpecial3_0 = 5000,
        AttackSpecial3_1 = 30000,
        AttackSpecial3_2 = 60000,
        AttackSpecial3_3 = 180000,
        AttackSpecial3_4 = 300000,
        AttackSpecial3_5 = 600000,
        AttackSpecial3_6 = 900000,
        AttackSpecial3_7 = 1800000,
        AttackSpecial3_8 = 3600000,
        AttackSpecial3_9 = 14400000,
        AttackSpecial3_10 = 43200000,
        AttackSpecial3_11 = 86400000,
        AttackSpecial3_12 = 259200000,
        AttackSpecial3_13 = 7200000,
        AttackSpecial3_14 = 0,
        AttackSpecial3_15 = 604800000,
        Default = 15000
    };

    #pragma pack(push, 1)
    struct MobQuestItem
    {
        UINT8 type;
        UINT8 typeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MobAttack
    {
        PAD(4);
        UINT16 type;
        bool enabled;
        PAD(1);
        UINT32 time;
        UINT8 range;
        PAD(1);
        UINT16 power;
        UINT16 addPower;
        Attribute attribute;
        UINT8 special;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MobItem
    {
        UINT32 grade;
        UINT32 dropRate;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MobInfo
    {
        UINT16 mobId;                 //0x00
        CharArray<32> mobName;        //0x02
        UINT16 level;                 //0x22
        UINT16 exp;                   //0x24
        UINT8 ai;                     //0x26
        PAD(1);
        UINT16 money1;                //0x28
        UINT16 money2;                //0x2A
        MobQuestItem questItem;       //0x2C
        PAD(2);
        UINT32 health;                //0x30
        UINT16 stamina;               //0x34
        UINT16 mana;                  //0x36
        UINT16 dexterity;             //0x38
        UINT16 wisdom;                //0x3A
        UINT16 luck;                  //0x3C
        UINT8 height;                 //0x3E
        UINT8 size;                   //0x3F
        Attribute attribute;          //0x40
        PAD(1);
        UINT16 defense;               //0x42
        UINT16 resistance;            //0x44
        MobResistState resistState;   //0x46
        MobResistSkill resistSkill;   //0x55
        PAD(1);
        UINT32 normalTime;            //0x5C
        UINT8 normalStep;             //0x60
        PAD(3);
        UINT32 chaseTime;             //0x64
        UINT8 chaseStep;              //0x68
        UINT8 chaseRange;             //0x69
        PAD(2);
        // 0x4A1A53
        MobCooldown cooldown;         //0x6C
        PAD(8);
        UINT32 country;               //0x78
        Array<MobAttack, 3> attacks;  //0x7C
        // 0xB8
        PAD(12);
        Array<MobItem, 9> items;      //0xC4
        // 0x10C
    };
    #pragma pack(pop)
}
