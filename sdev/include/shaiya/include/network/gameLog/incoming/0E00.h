#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/GameLogMain.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 123
    struct GameLogPvPLossIncoming
    {
        UINT16 opcode{ 0xE01 };
        GameLogMain main;
        ULONG targetId;
        CharArray<21> targetName;

        GameLogPvPLossIncoming() = default;

        GameLogPvPLossIncoming(CUser* killer, CUser* target)
            : main{}, targetId(target->connection.object.id), targetName(target->charName)
        {
            CUser::SetGameLogMain(killer, this);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 124
    struct GameLogPvPWinIncoming
    {
        UINT16 opcode{ 0xE02 };
        GameLogMain main;
        ULONG killerId;
        CharArray<21> killerName;

        GameLogPvPWinIncoming() = default;

        GameLogPvPWinIncoming(CUser* killer, CUser* target)
            : main{}, killerId(killer->connection.object.id), killerName(killer->charName)
        {
            CUser::SetGameLogMain(target, this);
        }
    };
    #pragma pack(pop)
}
