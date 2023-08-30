#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveGiftPointItemIncoming
    {
        UINT16 opcode{ 0xE03 };
        UserId userId;
        ProductCode productCode;
        CharName targetName;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };
    #pragma pack(pop)
}
