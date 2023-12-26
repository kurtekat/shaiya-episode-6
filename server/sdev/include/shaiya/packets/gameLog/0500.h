#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 131
    struct GameLogQuestStartIncoming
    {
        UINT16 opcode{ 0x501 };
        GameLogMain main;
        UINT16 questId;
        Array<char, 32> questName;
        UINT32 npcType;
        Array<char, 32> npcName;
    };

    // ActionType 133
    struct GameLogQuestEndIncoming
    {
        UINT16 opcode{ 0x502 };
        GameLogMain main;
        UINT16 questId;
        Array<char, 32> questName;
        bool success;
        UINT32 gold;
        UINT32 itemId;
        UINT8 itemCount;
        Array<char, 32> itemName;
    };
    #pragma pack(pop)
}
