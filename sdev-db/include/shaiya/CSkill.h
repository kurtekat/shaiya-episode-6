#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CSkill : SNode
    {
        uint16_t skillId;  //0x08
        uint8_t skillLv;   //0x0A
        uint8_t index;     //0x0B
        uint32_t delay;    //0x0C
        // 0x10
    };
    #pragma pack(pop)

    static_assert(sizeof(CSkill) == 0x10);
}
