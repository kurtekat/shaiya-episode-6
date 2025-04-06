#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogItem.h>

namespace shaiya
{
    enum struct GameLogItemGetType : uint8_t
    {
        ItemCreate = 1,
        ItemRemake
    };

    #pragma pack(push, 1)
    // TP_GAMELOG_ITEM_GET
    struct GameLogItemGet : GameLogItem
    {
        GameLogItemGetType getType;
        uint8_t count;

    };
    #pragma pack(pop)
}
