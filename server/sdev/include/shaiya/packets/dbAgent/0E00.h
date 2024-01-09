#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserPointSaveGiftPointItemIncoming
    {
        UINT16 opcode{ 0xE03 };
        UserId userId;
        ProductCode productCode;
        CharName targetName;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };

    struct UserPointReloadPointIncoming
    {
        UINT16 opcode{ 0xE06 };
        UserId userId;
    };

    struct UserPointReloadPointOutgoing
    {
        UINT16 opcode{ 0xE06 };
        UserId userId;
        UINT32 points;
    };

    struct UserPoint0E09Incoming
    {
        UINT16 opcode{ 0xE09 };
        UserId userId;
        CharId targetId;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };

    struct UserPoint0E0AIncoming
    {
        UINT16 opcode{ 0xE0A };
        UserId userId;
    };
    #pragma pack(pop)
}
