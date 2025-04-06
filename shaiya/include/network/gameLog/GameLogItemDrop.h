#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogItem.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_ITEM_DROP
    struct GameLogItemDrop : GameLogItem
    {
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
    };
    #pragma pack(pop)
}
