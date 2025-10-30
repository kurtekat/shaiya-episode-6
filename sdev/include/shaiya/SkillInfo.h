#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/SkillTypes.h>
#include "TypeValue.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct SkillInfo
    {
        uint16_t skillId;            //0x00
        uint8_t skillLv;             //0x02
        String<32> skillName;        //0x03
        PAD(1);
        uint16_t level;              //0x24
        Faction country;             //0x26
        bool fighter;                //0x27
        bool defender;               //0x28
        bool ranger;                 //0x29
        bool archer;                 //0x2A
        bool mage;                   //0x2B
        bool priest;                 //0x2C
        Grow grow;                   //0x2D
        uint8_t skillPoints;         //0x2E
        uint8_t typeShow;            //0x2F
        uint8_t typeAttack;          //0x30
        uint8_t typeEffect;          //0x31
        uint16_t typeDetail;         //0x32
        NeedWeapon needWeapon;       //0x34
        uint16_t needSP;             //0x44
        uint16_t needMP;             //0x46
        uint16_t readyTime;          //0x48
        uint16_t resetTime;          //0x4A
        uint8_t attackRange;         //0x4C
        SkillStatusType statusType;  //0x4D
        Attribute attribute;         //0x4E
        PAD(1);
        bool disable;                //0x50
        PAD(1);
        uint16_t prevSkillId;        //0x52
        uint8_t successType;         //0x54
        uint8_t successValue;        //0x55
        SkillTargetType targetType;  //0x56
        uint8_t applyRange;          //0x57
        uint8_t multiAttack;         //0x58
        PAD(3);
        uint32_t keepTime;           //0x5C
        uint8_t weapon1;             //0x60
        uint8_t weapon2;             //0x61
        uint8_t weaponValue;         //0x62
        uint8_t bag;                 //0x63
        uint16_t aggro;              //0x64
        uint16_t damageType;         //0x66
        uint16_t damageHP;           //0x68
        uint16_t damageSP;           //0x6A
        uint16_t damageMP;           //0x6C
        uint8_t timeDamageType;      //0x6E
        PAD(1);
        uint16_t timeDamageHP;       //0x70
        uint16_t timeDamageSP;       //0x72
        uint16_t timeDamageMP;       //0x74
        uint16_t damageAddHP;        //0x76
        uint16_t damageAddSP;        //0x78
        uint16_t damageAddMP;        //0x7A
        // 0x7C
        Array<TypeValue, 3> abilities;
        uint16_t healHP;             //0x88
        uint16_t healSP;             //0x8A
        uint16_t healMP;             //0x8C
        uint16_t timeHealHP;         //0x8E
        uint16_t timeHealSP;         //0x90
        uint16_t timeHealMP;         //0x92
        uint8_t defenseType;         //0x94
        uint8_t defenseValue;        //0x95 
        uint8_t limitHP;             //0x96
        uint8_t fixRange;            //0x97
        uint16_t changeType;         //0x98
        uint16_t changeLevel;        //0x9A
        bool32_t itemLink;           //0x9C
        PAD(4);
        // 0xA4
    };
    #pragma pack(pop)

    static_assert(sizeof(SkillInfo) == 0xA4);
}
