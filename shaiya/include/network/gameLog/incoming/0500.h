#pragma once
#include <shaiya/include/common.h>
#include <sdev/include/shaiya/include/GameLogMain.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 133
    struct GameLogQuestEndResultIncoming
    {
        UINT16 opcode{ 0x502 };
        GameLogMain main;
        UINT16 questId;
        CharArray<32> questName;
        bool success;
        UINT32 gold;
        UINT32 itemId;
        UINT8 itemCount;
        CharArray<32> itemName;
    };
    #pragma pack(pop)
}
