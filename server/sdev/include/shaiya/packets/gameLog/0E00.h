#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 123
    struct GameLogPvPLossIncoming
    {
        UINT16 opcode{ 0xE01 };
        GameLogMain killer;
        ULONG targetId;
        CharName targetName;
    };

    // ActionType 124
    struct GameLogPvPWinIncoming
    {
        UINT16 opcode{ 0xE02 };
        GameLogMain target;
        ULONG killerId;
        CharName killerName;
    };

    // ActionType 125
    struct GameLogPvPLeaveIncoming
    {
        UINT16 opcode{ 0xE03 };
        GameLogMain opponent;
        ULONG charId;
        CharName charName;
        PvPStatusType statType;
    };
    #pragma pack(pop)
}
