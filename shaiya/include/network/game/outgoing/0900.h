#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/QuestItemUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_QUEST_START
    struct GameQuestStartOutgoing
    {
        uint16_t opcode{ 0x902 };
        uint32_t npcId;
        uint16_t questId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_QUEST_END
    struct GameQuestEndOutgoing_EP5
    {
        uint16_t opcode{ 0x903 };
        uint32_t npcId;
        uint16_t questId;
        bool success;
        uint8_t resultIndex;
        uint32_t exp;
        uint32_t money;
        uint8_t itemBag;
        uint8_t itemSlot;
        uint8_t itemType;
        uint8_t itemTypeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_QUEST_END (6.0, 6.4)
    struct GameQuestEndOutgoing_EP6
    {
        uint16_t opcode{ 0x903 };
        uint32_t npcId;
        uint16_t questId;
        bool success;
        uint8_t resultIndex;
        uint32_t exp;
        uint32_t money;
        Array<QuestItemUnit, 3> itemList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_QUEST_END_SELECT
    struct GameQuestEndSelectOutgoing
    {
        uint16_t opcode{ 0x907 };
        uint16_t questId;
    };
    #pragma pack(pop)
}
