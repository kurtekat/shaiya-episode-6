#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ProductItemPurchaseResult : UINT8
    {
        Success,
        // or g_bDisableShop == true
        ProductInfoIsNull,
        InsufficientCash,
        InventoryFull
    };

    struct ProductItemPurchaseRequest
    {
        UINT16 opcode; // 0x2602
        char productCode[21];
    };

    struct ProductItemDefinition
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        // ep6 fields
        ULONG fromDate;
        ULONG toDate;
    };

    struct ProductItemPurchaseResponse
    {
        UINT16 opcode; // 0x2602
        ProductItemPurchaseResult result;
        UINT32 remainPoint;
        char productCode[21];
        ULONG purchaseDate;
        UINT32 usePoint;
        UINT8 itemCount;
        // size = itemCount (not 24)
        ProductItemDefinition item[24];
    };
    #pragma pack(pop)
}
