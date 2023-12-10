#pragma once
#include <include/shaiya/common.h>

// CUser::PacketShop

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemBagToNpcShopIncoming
    {
        UINT16 opcode{ 0x703 };
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
        ULONG npcId;
    };

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

    struct Item0711
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        #ifdef SHAIYA_EP6_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
        CraftName craftName;
    };

    struct UserBankItemListOutgoing
    {
        UINT16 opcode{ 0x711 };
        UINT32 bankMoney;
        UINT8 itemCount;
        #ifdef SHAIYA_EP6_ITEM_DURATION
        Array<Item0711, 40> itemList;
        #else
        Array<Item0711, 50> itemList;
        #endif
    };
    #pragma pack(pop)
}
