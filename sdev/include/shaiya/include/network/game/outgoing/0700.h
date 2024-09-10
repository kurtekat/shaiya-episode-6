#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

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
    struct Item0711
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
    struct UserBankItemListOutgoing
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
        Array<Item0711, 50> itemList;

        constexpr int size_without_list() { return 7; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item0711v2
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
    // 40 items (6.4 PT)
    struct UserBankItemListOutgoing2
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
        Array<Item0711v2, 40> itemList;

        constexpr int size_without_list() { return 7; }
    };
    #pragma pack(pop)
}
