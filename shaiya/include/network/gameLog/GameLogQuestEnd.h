#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogQuest.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_QUEST_END
    struct GameLogQuestEnd : GameLogQuest
    {
        bool success;
        uint32_t money;
        uint32_t itemId;
        uint8_t itemCount;
        String<32> itemName;
    };
    #pragma pack(pop)
}
