#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogItem.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_ITEM_REMAKE
    struct GameLogItemRemake : GameLogItem
    {
        uint64_t deleteUniqueId1;
        uint64_t deleteUniqueId2;
        uint64_t deleteUniqueId3;
    };
    #pragma pack(pop)
}
