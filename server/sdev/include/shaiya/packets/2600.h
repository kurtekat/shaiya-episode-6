#pragma once
#include <include/shaiya/common.h>

// CUser::PacketPoint

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct PointPurchaseItemResult : UINT8
    {
        Success,
        ProductCodeDoesNotExist,
        InsufficientPoints,
        InventoryFull
    };

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

    struct PointPurchaseItemIncoming
    {
        UINT16 opcode{ 0x2602 };
        ProductCode productCode;
    };

    struct Item2602
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        #ifdef SHAIYA_EP6_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
    };

    struct PointPurchaseItemOutgoing
    {
        UINT16 opcode{ 0x2602 };
        PointPurchaseItemResult result;
        UINT32 points;
        ProductCode productCode;
        ULONG purchaseDate;
        UINT32 itemPrice;
        UINT8 itemCount;
        // size = itemCount (not 24)
        Array<Item2602, 24> itemList;
    };

    struct PointSendGiftItemIncoming
    {
        UINT16 opcode{ 0x2603 };
        ProductCode productCode;
        CharName targetName;
    };

    struct PointSendGiftItemOutgoing
    {
        UINT16 opcode{ 0x2603 };
        PointSendGiftItemResult result;
        CharName targetName;
        UINT32 points;
        ProductCode productCode;
        ULONG purchaseDate;
        UINT32 itemPrice;
    };

    struct PointRecvGiftItemOutgoing
    {
        UINT16 opcode{ 0x2604 };
        CharName senderName;
        ProductCode productCode;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };

    struct PointIncoming
    {
        UINT16 opcode{ 0x2605 };
    };

    struct PointOutgoing
    {
        UINT16 opcode{ 0x2605 };
        UINT32 points;
    };

    struct Item2606
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };

    struct PointGiftItemListOutgoing
    {
        UINT16 opcode{ 0x2606 };
        UINT8 itemCount;
        // size = itemCount
        Array<Item2606, 240> itemList;
    };

    struct PointGiftItemBankToBagIncoming
    {
        UINT16 opcode{ 0x2607 };
        UINT8 srcSlot;
    };

    struct PointGiftItemBankToBagOutgoing
    {
        UINT16 opcode{ 0x2607 };
        UINT8 srcSlot;
        UINT8 destSlot;
        UINT8 destBag;
    };
    #pragma pack(pop)
}
