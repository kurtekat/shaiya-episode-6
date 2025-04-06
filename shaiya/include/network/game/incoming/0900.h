#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameQuestStartIncoming
    {
        uint16_t opcode{ 0x902 };
        uint32_t npcId;
        uint16_t questId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameQuestEndIncoming
    {
        uint16_t opcode{ 0x903 };
        uint32_t npcId;
        uint16_t questId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_QUEST_END_SELECT
    struct GameQuestEndSelectIncoming
    {
        uint16_t opcode{ 0x907 };
        uint16_t questId;
        uint8_t resultIndex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameQuestQuitIncoming
    {
        uint16_t opcode{ 0x908 };
        uint16_t questId;
    };
    #pragma pack(pop)
}
