#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogMain.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_QUEST
    struct GameLogQuest : GameLogMain
    {
        uint16_t questId;
        String<32> questName;
    };
    #pragma pack(pop)
}
