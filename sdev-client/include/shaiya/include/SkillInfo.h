#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SkillInfo
    {
        UINT16 skillId;  //0x00
        UINT8 skillLv;   //0x02
        PAD(15);
        UINT16 level;    //0x12
        PAD(38);
        UINT8 range;     //0x3A
        PAD(23);
        UINT32 damage;   //0x52
        PAD(298);
        // 0x180
    };
    #pragma pack(pop)
}
