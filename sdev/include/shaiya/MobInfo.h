#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>
#include "MobAttackInfo.h"
#include "MobItemDropInfo.h"

namespace shaiya
{
    enum struct MobTeam : int32_t
    {
        Light,
        Fury,
        Neutral
    };

    #pragma pack(push, 1)
    struct MobInfo
    {
        uint16_t mobId;           //0x00
        String<32> mobName;       //0x02
        uint16_t level;           //0x22
        uint16_t exp;             //0x24
        uint8_t ai;               //0x26
        PAD(1);
        uint16_t money;           //0x28
        uint16_t moneyAdd;        //0x2A
        uint8_t questItemType;    //0x2C
        uint8_t questItemTypeId;  //0x2D
        PAD(2);
        uint32_t health;          //0x30
        uint16_t stamina;         //0x34
        uint16_t mana;            //0x36
        uint16_t dexterity;       //0x38
        uint16_t wisdom;          //0x3A
        uint16_t luck;            //0x3C
        // Day
        uint8_t height;           //0x3E
        uint8_t size;             //0x3F
        Attribute attribute;      //0x40
        PAD(1);
        uint16_t defense;         //0x42
        uint16_t resistance;      //0x44
        // 0x46
        Array<bool, 15> resistStates;
        // 0x55
        Array<uint8_t, 6> resistSkills;
        PAD(1);
        uint32_t normalTime;      //0x5C
        uint8_t normalStep;       //0x60
        PAD(3);
        uint32_t chaseTime;       //0x64
        uint8_t chaseStep;        //0x68
        uint8_t chaseRange;       //0x69
        PAD(2);
        // 0x4A1A53
        uint32_t respawnTime;     //0x6C
        // AttackTime3
        uint32_t defenseAdd;      //0x70
        // Attack3
        uint32_t recoverValue;    //0x74
        MobTeam country;          //0x78
        bool isObelisk;           //0x7C
        PAD(3);
        // 0x80
        Array<MobAttackInfo, 3> attacks;
        // 0xBC
        Array<MobItemDropInfo, 10> dropInfo;
        // 0x10C
    };
    #pragma pack(pop)

    static_assert(sizeof(MobInfo) == 0x10C);
}
