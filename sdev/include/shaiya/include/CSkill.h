#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    struct SkillInfo;

    #pragma pack(push, 1)
    struct CSkill
    {
        SNode node;             //0x00
        ULONG id;               //0x08
        UINT32 skillId;         //0x0C
        UINT32 skillLv;         //0x10
        // CUser->skillList
        UINT32 skillListIndex;  //0x14
        PAD(8);
        DWORD resetTime;        //0x20
        DWORD applyTime;        //0x24
        PAD(8);
        // CUser->id, CMob->id
        ULONG debuffCasterId;   //0x30
        SkillInfo* skillInfo;   //0x34
        // 0x38
    };
    #pragma pack(pop)
}
