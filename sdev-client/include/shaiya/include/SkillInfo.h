#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SkillAbility
    {
        Array<UINT8, 10> type;
        Array<UINT16, 10> value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillWeapon
    {
        bool oneHandedSword;
        bool twoHandedSword;
        bool oneHandedAxe;
        bool twoHandedAxe;
        bool dualWeapon;
        bool spear;
        bool oneHandedBlunt;
        bool twoHandedBlunt;
        bool reverseDagger;
        bool dagger;
        bool javelin;
        bool staff;
        bool bow;
        bool crossbow;
        bool knuckles;
        bool shield;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillInfo
    {
        UINT16 skillId;          //0x00
        UINT8 skillLv;           //0x02
        PAD(1);
        char* skillName;         //0x04
        UINT16 icon;             //0x08
        PAD(8);
        UINT16 reqLevel;         //0x12
        UINT16 skillPoint;       //0x14
        PAD(7);
        UINT8 typeShow;          //0x1D
        UINT8 typeAttack;        //0x1E
        UINT8 typeEffect;        //0x1F
        UINT16 typeDetail;       //0x20
        SkillWeapon needWeapon;  //0x22
        UINT16 stamina;          //0x32
        UINT16 mana;             //0x34
        UINT16 readyTime;        //0x36
        UINT16 resetTime;        //0x38
        UINT8 range;             //0x3A
        PAD(13);
        ULONG keepTime;          //0x48
        PAD(6);
        UINT32 damage;           //0x52
        PAD(16);
        SkillAbility ability;    //0x66
        // 0x84
        PAD(24);
        // 0x9C
    };

    #pragma pack(pop)
}
