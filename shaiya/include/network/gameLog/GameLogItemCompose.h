#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/network/gameLog/GameLogItem.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_ITEM_COMPOSE
    struct GameLogItemCompose : GameLogItem
    {
        uint64_t composeUniqueId;
        uint32_t composeItemId;
        CraftName oldCraftName;
    };
    #pragma pack(pop)
}
