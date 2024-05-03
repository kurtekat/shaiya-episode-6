#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

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
#ifdef SHAIYA_EP6_4_PT
        ULONG fromDate;
        ULONG toDate;
#endif
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MyShopItemListOutgoing
    {
        UINT16 opcode{ 0x230B };
        UINT8 itemCount;
        Array<Item230B, 20> itemList;

        constexpr int size_without_list() { return 3; }
    };
    #pragma pack(pop)
}
