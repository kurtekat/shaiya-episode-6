#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/item/CraftName.h>
#include <shaiya/include/item/Gems.h>

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
#ifdef SHAIYA_EP6_4_PT
        ULONG fromDate;
        ULONG toDate;
#endif
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserBankItemListOutgoing
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
#ifdef SHAIYA_EP6_4_PT
        std::array<Item0711, 40> itemList;
#else
        std::array<Item0711, 50> itemList;
#endif

        constexpr int size_without_list() { return 7; }
    };
    #pragma pack(pop)
}
