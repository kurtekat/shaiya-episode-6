#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 210
    struct GameLogEnterRaidPartyIncoming
    {
        UINT16 opcode{ 0xF01 };
        GameLogMain main;
        ULONG partyId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 211
    struct GameLogLeaveRaidPartyIncoming
    {
        UINT16 opcode{ 0xF02 };
        GameLogMain main;
        ULONG partyId;
    };
    #pragma pack(pop)
}
