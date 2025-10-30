#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Attribute.h>

namespace shaiya
{
    struct SkillInfo;

    #pragma pack(push, 1)
    struct MobAttackInfo
    {
        uint16_t type;          //0x00
        uint8_t okay;           //0x02
        PAD(1);
        uint32_t time;          //0x04
        uint8_t range;          //0x08
        PAD(1);
        uint16_t damage;        //0x0A
        uint16_t damageAdd;     //0x0C
        Attribute attribute;    //0x0E
        uint8_t special;        //0x0F
        SkillInfo* skillInfo;   //0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(MobAttackInfo) == 0x14);
}
