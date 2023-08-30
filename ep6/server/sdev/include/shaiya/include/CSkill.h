#pragma once
#include <shaiya/common.h>
#include <shaiya/include/CGameData.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CSkill
    {
        PAD(8);
        ULONG id;        //0x08
        UINT32 skillId;  //0x0C
        UINT32 skillLv;  //0x10
        UINT32 index;    //0x14
        PAD(28);
        // 0x34
        CGameData::SkillInfo* skillInfo;
        PAD(8);
        // 0x40
    };
    #pragma pack(pop)
}
