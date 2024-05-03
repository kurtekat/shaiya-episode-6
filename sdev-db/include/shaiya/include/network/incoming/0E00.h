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
        CharArray<21> targetName;
        CharArray<21> productCode;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentReloadPointIncoming
    {
        UINT16 opcode{ 0xE06 };
        ULONG userId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentSaveBuyPointItemIncoming
    {
        UINT16 opcode{ 0xE0A };
        ULONG userId;
    };
    #pragma pack(pop)
}
