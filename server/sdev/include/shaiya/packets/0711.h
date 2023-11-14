#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item0711
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        #ifdef WITH_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
        CraftName craftName;
    };

    struct UserStoredItemListOutgoing
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
        #ifdef WITH_ITEM_DURATION
        Array<Item0711, 40> itemList;
        #else
        Array<Item0711, 50> itemList;
        #endif
    };
    #pragma pack(pop)
}
