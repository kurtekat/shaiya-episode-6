#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

// CUser::PacketShop

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemBagToNpcShopOutgoing
    {
        UINT16 opcode{ 0x703 };
        UINT8 result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item0711_EP5
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 50 items (5.4, 6.0)
    struct UserBankItemListOutgoing_EP5
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
        Array<Item0711_EP5, 50> itemList;

        constexpr static int baseLength = 7;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item0711_EP6_4
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        ULONG fromDate;
        ULONG toDate;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 40 items (6.4)
    struct UserBankItemListOutgoing_EP6_4
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
        Array<Item0711_EP6_4, 40> itemList;

        constexpr static int baseLength = 7;
    };
    #pragma pack(pop)
}
