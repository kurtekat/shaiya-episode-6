#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include "CObject.h"
#include "SNode.h"

namespace shaiya
{
    struct SkillInfo;

    #pragma pack(push, 1)
    struct CTrap : SNode, CObject
    {
        uint32_t userId;       //0x30
        Country country;       //0x34
        PAD(3);
        tick32_t endTime;      //0x38
        SkillInfo* skillInfo;  //0x3C
        // 0x40
    };
    #pragma pack(pop)

    static_assert(sizeof(CTrap) == 0x40);
}
