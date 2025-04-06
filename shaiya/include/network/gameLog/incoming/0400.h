#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogItemCompose.h>
#include <shaiya/include/network/gameLog/GameLogItemDrop.h>
#include <shaiya/include/network/gameLog/GameLogItemGet.h>
#include <shaiya/include/network/gameLog/GameLogItemRemake.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 111
    struct GameLogItemGetIncoming
    {
        GameLogItemGet packet{ 0x401 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 112
    struct GameLogItemDropIncoming
    {
        GameLogItemDrop packet{ 0x402 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 213
    struct GameLogItemComposeIncoming
    {
        GameLogItemCompose packet{ 0x427 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 215
    struct GameLogItemRemakeIncoming
    {
        GameLogItemRemake packet{ 0x429 };
    };
    #pragma pack(pop)
}
