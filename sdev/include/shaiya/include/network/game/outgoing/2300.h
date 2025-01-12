#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

// CUser::PacketMyShop

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item230B_EP5
    {
        UINT8 slot;
        UINT32 price;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MyShopItemListOutgoing_EP5
    {
        UINT16 opcode{ 0x230B };
        UINT8 itemCount;
        Array<Item230B_EP5, 20> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item230B_EP6_4
    {
        UINT8 slot;
        UINT32 price;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        ULONG fromDate;
        ULONG toDate;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MyShopItemListOutgoing_EP6_4
    {
        UINT16 opcode{ 0x230B };
        UINT8 itemCount;
        Array<Item230B_EP6_4, 20> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
