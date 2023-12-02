#pragma once
#include <include/shaiya/common.h>

// CUser::PacketMyShop

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item230B
    {
        UINT8 slot;
        UINT32 price;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        #ifdef WITH_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
        Gems gems;
        CraftName craftName;
    };

    struct MyShopItemListOutgoing
    {
        UINT16 opcode{ 0x230B };
        UINT8 itemCount;
        Array<Item230B, 20> itemList;
    };
    #pragma pack(pop)
}
