#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/network/gameLog/GameLogMain.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_ITEM
    struct GameLogItem : GameLogMain
    {
        uint64_t uniqueId;
        uint32_t itemId;
        ItemName itemName;
        Gems gems;
        MakeTime makeTime;
        CraftName craftName;
    };
    #pragma pack(pop)
}
