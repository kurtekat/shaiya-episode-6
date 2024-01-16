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
        CharName targetName;
        ProductCode productCode;
        UINT32 itemPrice;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserPointItemGetIncoming
    {
        UINT16 opcode{ 0xE05 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT64 uniqueId;
        UINT32 itemId;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
        ULONG makeTime;
        ItemMakeType makeType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserPointReloadPointIncoming
    {
        UINT16 opcode{ 0xE06 };
        UserId userId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserPointReloadPointOutgoing
    {
        UINT16 opcode{ 0xE06 };
        UserId userId;
        UINT32 points;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserPointAddPointOutgoing
    {
        UINT16 opcode{ 0xE08 };
        UserId userId;
        UINT32 addPoints;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserPoint0E09Incoming
    {
        UINT16 opcode{ 0xE09 };
        UserId userId;
        CharId targetId;
        ULONG purchaseDate;
        UINT32 purchaseNumber;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserPointSaveBuyPointItemIncoming
    {
        UINT16 opcode{ 0xE0A };
        UserId userId;
    };
    #pragma pack(pop)
}
