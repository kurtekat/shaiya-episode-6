#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    enum struct GameLogType0401 : UINT8
    {
        None,
        ItemCreate,
        Remake
    };

    #pragma pack(push, 1)
    // ActionType 111
    struct GameLogItemCreateIncoming
    {
        UINT16 opcode{ 0x401 };
        GameLogMain main;
        UINT64 itemUid;
        UINT32 itemId;
        Array<char, 32> itemName;
        Gems gems;
        ULONG makeTime;
        CraftName craftName;
        GameLogType0401 type;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 112
    struct GameLogItemRemoveIncoming
    {
        UINT16 opcode{ 0x402 };
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
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 213
    struct GameLogItemComposeIncoming
    {
        UINT16 opcode{ 0x427 };
        GameLogMain main;
        UINT64 itemUid;
        UINT32 itemId;
        Array<char, 32> itemName;
        Gems gems;
        ULONG makeTime;
        CraftName craftName;
        UINT64 oldItemUid;
        UINT32 oldItemId;
        CraftName oldCraftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 215
    struct GameLogItemRemakeIncoming
    {
        UINT16 opcode{ 0x429 };
        GameLogMain main;
        UINT64 itemUid;
        UINT32 itemId;
        Array<char, 32> itemName;
        Gems gems;
        ULONG makeTime;
        CraftName craftName;
        UINT64 oldItemUid1;
        UINT64 oldItemUid2;
        UINT64 oldItemUid3;
    };
    #pragma pack(pop)
}
