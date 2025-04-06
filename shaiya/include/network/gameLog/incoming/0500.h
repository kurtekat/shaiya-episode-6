#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/gameLog/GameLogQuestEnd.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 133
    struct GameLogQuestEndIncoming
    {
        GameLogQuestEnd packet{ 0x502 };
    };
    #pragma pack(pop)
}
