#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketUserPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentPointGiftItemIncoming
    {
        UINT16 opcode{ 0xE03 };
        ULONG userId;
        CharName targetName;
        ProductCode productCode;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPointReloadIncoming
    {
        UINT16 opcode{ 0xE06 };
        ULONG userId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPointUpdateIncoming
    {
        UINT16 opcode{ 0xE0A };
        ULONG userId;
    };
    #pragma pack(pop)
}
