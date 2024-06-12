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

        PointPurchaseItemIncoming() = default;

        PointPurchaseItemIncoming(const char* productCode)
            : productCode{}
        {
            StringCbCopyA(this->productCode.data(), this->productCode.size(), productCode);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointSendGiftItemIncoming
    {
        UINT16 opcode{ 0x2603 };
        CharArray<21> productCode;
        CharArray<21> targetName;

        PointSendGiftItemIncoming() = default;

        PointSendGiftItemIncoming(const char* productCode, const char* targetName)
            : productCode{}, targetName{}
        {
            StringCbCopyA(this->productCode.data(), this->productCode.size(), productCode);
            StringCbCopyA(this->targetName.data(), this->targetName.size(), targetName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointIncoming
    {
        UINT16 opcode{ 0x2605 };

        PointIncoming() = default;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PointGiftItemBankToBagIncoming
    {
        UINT16 opcode{ 0x2607 };
        UINT8 srcSlot;

        PointGiftItemBankToBagIncoming() = default;

        PointGiftItemBankToBagIncoming(UINT8 srcSlot)
            : srcSlot(srcSlot)
        {
        }
    };
    #pragma pack(pop)
}
