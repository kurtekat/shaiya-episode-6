#pragma once
#include <shaiya/include/common.h>
#include <sdev/include/shaiya/include/CUser.h>
#include <sdev/include/shaiya/include/GameLogMain.h>

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
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 162
    struct GameLog0802Incoming
    {
        UINT16 opcode{ 0x802 };
        GameLogMain main;
        UINT64 itemUid;
        UINT32 itemId;
        std::array<char, 32> itemName;
        Gems gems;
        ULONG makeTime;
        CraftName craftName;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
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
