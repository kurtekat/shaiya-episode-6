#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MyShopItem
    {
        UINT8 index;
        UINT32 price;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        // or CloakBadge
        UINT8 gems[6];
        #ifdef SHAIYA_EP6
        ULONG fromDate;
        ULONG toDate;
        #endif
        char craftName[21];
    };

    struct MyShopItemList
    {
        UINT16 opcode; // 0x230B
        UINT8 itemCount;
        MyShopItem inventory[20];
    };
    #pragma pack(pop)
}
