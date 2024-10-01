#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketUserPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentPointGiftItemIncoming
    {
        UINT16 opcode{ 0xE03 };
        ULONG userId;
        CharArray<21> targetName;
        CharArray<21> productCode;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;

        DBAgentPointGiftItemIncoming() = default;

        DBAgentPointGiftItemIncoming(
            ULONG userId, 
            const char* targetName, 
            const char* productCode, 
            UINT32 itemPrice, 
            ULONG purchaseDate, 
            UINT32 purchaseNumber
        )
            : userId(userId), targetName{}, productCode{}, itemPrice(itemPrice), purchaseDate(purchaseDate), purchaseNumber(purchaseNumber)
        {
            StringCbCopyA(this->targetName.data(), this->targetName.size(), targetName);
            StringCbCopyA(this->productCode.data(), this->productCode.size(), productCode);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPointReloadIncoming
    {
        UINT16 opcode{ 0xE06 };
        ULONG userId;

        DBAgentPointReloadIncoming() = default;

        DBAgentPointReloadIncoming(ULONG userId)
            : userId(userId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPointUpdateIncoming
    {
        UINT16 opcode{ 0xE0A };
        ULONG userId;

        DBAgentPointUpdateIncoming() = default;

        DBAgentPointUpdateIncoming(ULONG userId)
            : userId(userId)
        {
        }
    };
    #pragma pack(pop)
}
