#pragma once
#include <shaiya/include/common.h>

// CUser::PacketQuest

namespace shaiya
{
    #pragma pack(push, 1)
    struct QuestStartIncoming
    {
        UINT16 opcode{ 0x902 };
        ULONG npcId;
        UINT16 questId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndResultIncoming
    {
        UINT16 opcode{ 0x903 };
        ULONG npcId;
        UINT16 questId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndSelectIncoming
    {
        UINT16 opcode{ 0x907 };
        UINT16 questId;
        UINT8 byResultIndex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestQuitIncoming
    {
        UINT16 opcode{ 0x908 };
        UINT16 questId;
    };
    #pragma pack(pop)
}
