#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketUserPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentSaveGiftPointItemIncoming
    {
        UINT16 opcode{ 0xE03 };
        ULONG userId;
        CharName targetName;
        ProductCode productCode;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;

        DBAgentSaveGiftPointItemIncoming() = default;

        DBAgentSaveGiftPointItemIncoming(ULONG userId, const char* targetName, const char* productCode, UINT32 itemPrice, ULONG purchaseDate, UINT32 purchaseNumber)
            : userId(userId), targetName{}, productCode{}, itemPrice(itemPrice), purchaseDate(purchaseDate), purchaseNumber(purchaseNumber)
        {
            StringCbCopyA(this->targetName.data(), this->targetName.size(), targetName);
            StringCbCopyA(this->productCode.data(), this->productCode.size(), productCode);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentReloadPointIncoming
    {
        UINT16 opcode{ 0xE06 };
        ULONG userId;

        DBAgentReloadPointIncoming() = default;

        DBAgentReloadPointIncoming(ULONG userId)
            : userId(userId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSaveBuyPointItemIncoming
    {
        UINT16 opcode{ 0xE0A };
        ULONG userId;

        DBAgentSaveBuyPointItemIncoming() = default;

        DBAgentSaveBuyPointItemIncoming(ULONG userId)
            : userId(userId)
        {
        }
    };
    #pragma pack(pop)
}
