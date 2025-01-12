#pragma once
#include <shaiya/include/common.h>

// CUser::PacketQuest

namespace shaiya
{
    #pragma pack(push, 1)
    struct QuestStartOutgoing
    {
        UINT16 opcode{ 0x902 };
        ULONG npcId;
        UINT16 questId;

        QuestStartOutgoing() = default;

        QuestStartOutgoing(ULONG npcId, UINT16 questId)
            : npcId(npcId), questId(questId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndResultOutgoing_EP5
    {
        UINT16 opcode{ 0x903 };
        ULONG npcId;
        UINT16 questId;
        bool success;
        UINT8 index;
        UINT32 exp;
        UINT32 gold;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;

        QuestEndResultOutgoing_EP5() = default;

        QuestEndResultOutgoing_EP5(ULONG npcId, UINT16 questId, bool success, UINT8 index, UINT32 exp, UINT32 gold, 
            UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId
        )
        {
            this->npcId = npcId;
            this->questId = questId;
            this->success = success;
            this->index = index;
            this->exp = exp;
            this->gold = gold;
            this->bag = bag;
            this->slot = slot;
            this->type = type;
            this->typeId = typeId;
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item0903
    {
        UINT8 count;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
    };
    #pragma pack(pop)

    using ItemList0903 = Array<Item0903, 3>;

    #pragma pack(push, 1)
    // 6.0, 6.4
    struct QuestEndResultOutgoing_EP6
    {
        UINT16 opcode{ 0x903 };
        ULONG npcId;
        UINT16 questId;
        bool success;
        UINT8 index;
        UINT32 exp;
        UINT32 gold;
        ItemList0903 itemList;

        QuestEndResultOutgoing_EP6() = default;

        QuestEndResultOutgoing_EP6(ULONG npcId, UINT16 questId, bool success, UINT8 index, UINT32 exp, UINT32 gold, const ItemList0903& itemList)
            : npcId(npcId), questId(questId), success(success), index(index), exp(exp), gold(gold), itemList(itemList)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndSelectOutgoing
    {
        UINT16 opcode{ 0x907 };
        UINT16 questId;

        QuestEndSelectOutgoing() = default;

        QuestEndSelectOutgoing(UINT16 questId)
            : questId(questId)
        {
        }
    };
    #pragma pack(pop)
}
