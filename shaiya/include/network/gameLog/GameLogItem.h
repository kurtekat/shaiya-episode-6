#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/network/gameLog/GameLogMain.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GAMELOG_ITEM
    struct GameLogItem : GameLogMain
    {
        uint64_t uniqueId;
        uint32_t itemId;
        String<32> itemName;
        Gems gems;
        time32_t makeTime;
        CraftName craftName;
    };
    #pragma pack(pop)
}
