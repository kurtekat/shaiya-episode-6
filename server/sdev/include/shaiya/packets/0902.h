#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct QuestStartIncoming
    {
        UINT16 opcode{ 0x902 };
        ULONG npcId;
        UINT16 questId;
    };

    struct QuestStartOutgoing
    {
        UINT16 opcode{ 0x902 };
        ULONG npcId;
        UINT16 questId;
    };
    #pragma pack(pop)
}
