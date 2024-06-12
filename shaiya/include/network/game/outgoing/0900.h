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

    #pragma pack(push, 1)
    struct QuestEndResultOutgoing
    {
        UINT16 opcode{ 0x903 };
        ULONG npcId;
        UINT16 questId;
        bool success;
        UINT8 index;
        UINT32 exp;
        UINT32 gold;
#ifdef SHAIYA_EP6_4_PT
        Array<Item0903, 3> itemList;
#else
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
#endif
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestEndSelectOutgoing
    {
        UINT16 opcode{ 0x907 };
        UINT16 questId;
    };
    #pragma pack(pop)
}
