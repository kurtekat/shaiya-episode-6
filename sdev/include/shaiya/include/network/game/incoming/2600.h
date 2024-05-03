#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct PointPurchaseItemIncoming
    {
        UINT16 opcode{ 0x2602 };
        CharArray<21> productCode;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointSendGiftItemIncoming
    {
        UINT16 opcode{ 0x2603 };
        CharArray<21> productCode;
        CharArray<21> targetName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointIncoming
    {
        UINT16 opcode{ 0x2605 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointGiftItemBankToBagIncoming
    {
        UINT16 opcode{ 0x2607 };
        UINT8 srcSlot;
    };
    #pragma pack(pop)
}
