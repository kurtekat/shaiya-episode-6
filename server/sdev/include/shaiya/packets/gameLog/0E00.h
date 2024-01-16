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
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 124
    struct GameLogPvPWinIncoming
    {
        UINT16 opcode{ 0xE02 };
        GameLogMain target;
        ULONG killerId;
        CharName killerName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
