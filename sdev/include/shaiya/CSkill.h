#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"
#include "Target.h"

namespace shaiya
{
    struct SkillInfo;

    #pragma pack(push, 1)
    struct CSkill : SNode
    {
        uint32_t id;          //0x08
        int32_t skillId;      //0x0C
        int32_t skillLv;      //0x10
        int32_t index;        //0x14
        tick32_t attackTime;  //0x18
        tick32_t resetTime;   //0x1C
        tick32_t endTime;     //0x20
        tick32_t prevTime;    //0x24
        PAD(4);
        Target attacker;      //0x2C
        SkillInfo* info;      //0x34
        // 0x38
    };
    #pragma pack(pop)

    static_assert(sizeof(CSkill) == 0x38);
}
