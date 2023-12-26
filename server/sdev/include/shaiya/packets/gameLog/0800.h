#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 161
    struct GameLogMoneyPickIncoming
    {
        UINT16 opcode{ 0x801 };
        GameLogMain main;
        UINT32 pickMoney;
        UINT32 money;
    };

    // ActionType 162
    struct GameLog0802Incoming
    {
        UINT16 opcode{ 0x802 };
        GameLogMain main;
        UINT64 itemUid;
        UINT32 itemId;
        Array<char, 32> itemName;
        Gems gems;
        ULONG makeTime;
        CraftName craftName;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };

    // ActionType 163
    struct GameLogMoneyExcToIncoming
    {
        UINT16 opcode{ 0x803 };
        GameLogMain main;
        UINT32 excMoney;
        UINT32 money;
        ULONG excCharId;
        CharName excCharName;
    };

    // ActionType 164
    struct GameLogMoneyExcFromIncoming
    {
        UINT16 opcode{ 0x804 };
        GameLogMain main;
        UINT32 excMoney;
        UINT32 money;
        ULONG excCharId;
        CharName excCharName;
        // to-do?
        PAD(19);
    };

    // ActionType 164
    struct GameLogMoneyExcPvPFromIncoming
    {
        UINT16 opcode{ 0x805 };
        GameLogMain main;
        UINT32 excMoney;
        UINT32 money;
        ULONG excCharId;
        CharName excCharName;
        // to-do?
        PAD(19);
    };
    #pragma pack(pop)
}
