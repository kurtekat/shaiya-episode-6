#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 32> MobName;

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
        UINT16 mobId;            //0x00
        MobName mobName;         //0x02
        UINT16 level;            //0x22
        UINT16 exp;              //0x24
        UINT8 ai;                //0x26
        PAD(1);
        UINT16 money1;           //0x28
        UINT16 money2;           //0x2A
        MobQuestItem questItem;  //0x2C
        PAD(2);
        UINT32 health;           //0x30
        UINT16 stamina;          //0x34
        UINT16 mana;             //0x36
        UINT16 dexterity;        //0x38
        UINT16 wisdom;           //0x3A
        UINT16 luck;             //0x3C
        UINT8 height;            //0x3E
        UINT8 size;              //0x3F
        Attribute attribute;     //0x40
        PAD(1);
        UINT16 defense;          //0x42
        UINT16 resistance;       //0x44
        // 0x46
        Array<bool, 15> resistState;
        // 0x55
        Array<UINT8, 6> resistSkill;
        UINT32 normalTime;       //0x5C
        UINT8 normalStep;        //0x60
        PAD(3);
        UINT32 chaseTime;        //0x64
        UINT8 chaseStep;         //0x68
        UINT8 chaseRange;        //0x69 
        PAD(2);
        // 0x4A1A53
        DWORD cooldown;          //0x6C
        PAD(8);
        UINT32 country;          //0x78
        // 0x7C
        Array<MobAttack, 3> attack;
        // 0xB8
        PAD(12);
        // 0xC4
        Array<MobItem, 9> mobItem;
        // 0x10C
    };
    #pragma pack(pop)
}
