#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/SkillTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SkillAbility
    {
        Array<SkillAbilityType, 10> type;
        Array<uint16_t, 10> value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillInfo
    {
        uint16_t skillId;        //0x00
        uint8_t skillLv;         //0x02
        PAD(1);
        char* skillName;         //0x04
        uint16_t icon;           //0x08
        PAD(8);
        uint16_t level;          //0x12
        uint16_t skillPoints;    //0x14
        PAD(7);
        uint8_t typeShow;        //0x1D
        uint8_t typeAttack;      //0x1E
        uint8_t typeEffect;      //0x1F
        uint16_t typeDetail;     //0x20
        NeedWeapon needWeapon;   //0x22
        uint16_t stamina;        //0x32
        uint16_t mana;           //0x34
        uint16_t readyTime;      //0x36
        uint16_t resetTime;      //0x38
        uint8_t range;           //0x3A
        PAD(13);
        uint32_t keepTime;       //0x48
        PAD(6);
        uint32_t damage;         //0x52
        PAD(16);
        SkillAbility abilities;  //0x66
        // 0x84
        PAD(24);
        // 0x9C
    };
    #pragma pack(pop)

    static_assert(sizeof(SkillInfo) == 0x9C);
}
