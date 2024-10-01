#pragma once
#include <shaiya/include/common.h>

// CUser::PacketPoint

namespace shaiya
{
    enum struct PointBuyItemResult : UINT8
    {
        Success,
        ProductCodeDoesNotExist,
        InsufficientPoints,
        InventoryFull
    };

    #pragma pack(push, 1)
    struct Item2602
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointBuyItemOutgoing
    {
        UINT16 opcode{ 0x2602 };
        PointBuyItemResult result;
        UINT32 points;
        CharArray<21> productCode;
        ULONG purchaseDate;
        UINT32 itemPrice;
        UINT8 itemCount;
        Array<Item2602, 24> itemList;

        constexpr int size_without_list() { return 37; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item2602v2
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        ULONG fromDate;
        ULONG toDate;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointBuyItemOutgoing2
    {
        UINT16 opcode{ 0x2602 };
        PointBuyItemResult result;
        UINT32 points;
        CharArray<21> productCode;
        ULONG purchaseDate;
        UINT32 itemPrice;
        UINT8 itemCount;
        Array<Item2602v2, 24> itemList;

        constexpr int size_without_list() { return 37; }
    };
    #pragma pack(pop)

    enum struct PointSendGiftItemResult : UINT8
    {
        Success,
        CharNameDoesNotExist,
        CannotSendPresent,
        ItemCountExceeded,
        InsufficientSlots,
        InsertFailure,
        ProductCodeDoesNotExist,
        CannotDeductPoints,
        LogInsertFailure,
        PreviousRequestInProcess,
        InsufficientPoints
    };

    #pragma pack(push, 1)
    struct PointSendGiftItemOutgoing
    {
        UINT16 opcode{ 0x2603 };
        PointSendGiftItemResult result;
        CharArray<21> targetName;
        UINT32 points;
        CharArray<21> productCode;
        ULONG purchaseDate;
        UINT32 itemPrice;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointRecvGiftItemOutgoing
    {
        UINT16 opcode{ 0x2604 };
        CharArray<21> senderName;
        CharArray<21> productCode;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointBalanceOutgoing
    {
        UINT16 opcode{ 0x2605 };
        UINT32 points;

        PointBalanceOutgoing() = default;

        PointBalanceOutgoing(UINT32 points)
            : points(points)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item2606
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointGiftItemListOutgoing
    {
        UINT16 opcode{ 0x2606 };
        UINT8 itemCount;
        Array<Item2606, 240> itemList;

        constexpr int size_without_list() { return 3; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointGiftItemBankToBagOutgoing
    {
        UINT16 opcode{ 0x2607 };
        UINT8 srcSlot;
        UINT8 destSlot;
        UINT8 destBag;

        PointGiftItemBankToBagOutgoing() = default;

        PointGiftItemBankToBagOutgoing(UINT8 srcSlot, UINT8 destSlot, UINT8 destBag)
            : srcSlot(srcSlot), destSlot(destSlot), destBag(destBag)
        {
        }
    };
    #pragma pack(pop)
}
