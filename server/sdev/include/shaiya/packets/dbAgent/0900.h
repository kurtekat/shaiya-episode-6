#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentSkillApplyIncoming
    {
        UINT16 opcode{ 0x901 };
        ULONG userId;
        UINT16 skillId;
        UINT8 skillLv;
        ULONG keepTime;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSkillRemoveIncoming
    {
        UINT16 opcode{ 0x902 };
        ULONG userId;
        UINT16 skillId;
        UINT8 skillLv;
    };
    #pragma pack(pop)
}
