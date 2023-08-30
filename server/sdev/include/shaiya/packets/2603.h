#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct PresentPurchaseResult : UINT8
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

    struct PresentPurchaseIncoming
    {
        UINT16 opcode{ 0x2603 };
        ProductCode productCode;
        CharName targetName;
    };

    struct PresentPurchaseOutgoing
    {
        UINT16 opcode{ 0x2603 };
        PresentPurchaseResult result;
        CharName targetName;
        UINT32 points;
        ProductCode productCode;
        ULONG purchaseDate;
        UINT32 itemPrice;
    };
    #pragma pack(pop)
}
