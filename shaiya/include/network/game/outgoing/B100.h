#pragma once
#include <shaiya/include/common.h>

// CUser::PacketBilling

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemB101
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BillingItemListOutgoing
    {
        UINT16 opcode{ 0xB101 };
        UINT8 itemCount;
        std::array<ItemB101, 240> itemList;

        constexpr int size_without_list() { return 3; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BillingItemBankToBagOutgoing
    {
        UINT16 opcode{ 0xB102 };
        UINT8 srcSlot;
        UINT8 destSlot;
        UINT8 destBag;
    };
    #pragma pack(pop)
}
