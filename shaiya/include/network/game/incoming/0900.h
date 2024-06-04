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

        QuestStartIncoming() = default;

        QuestStartIncoming(ULONG npcId, UINT16 questId)
            : npcId(npcId), questId(questId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndResultIncoming
    {
        UINT16 opcode{ 0x903 };
        ULONG npcId;
        UINT16 questId;

        QuestEndResultIncoming() = default;

        QuestEndResultIncoming(ULONG npcId, UINT16 questId)
            : npcId(npcId), questId(questId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndSelectIncoming
    {
        UINT16 opcode{ 0x907 };
        UINT16 questId;
        UINT8 byResultIndex;

        QuestEndSelectIncoming() = default;

        QuestEndSelectIncoming(UINT16 questId, UINT8 byResultIndex)
            : questId(questId), byResultIndex(byResultIndex)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestQuitIncoming
    {
        UINT16 opcode{ 0x908 };
        UINT16 questId;

        QuestQuitIncoming() = default;

        QuestQuitIncoming(UINT16 questId)
            : questId(questId)
        {
        }
    };
    #pragma pack(pop)
}
