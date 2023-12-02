#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserItem

namespace shaiya
{
    #pragma pack(push, 1)
    // inventory
    struct UserItemDeleteIncoming
    {
        UINT16 opcode{ 0x702 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };

    struct UserItemBagToBankIncoming
    {
        UINT16 opcode{ 0x704 };
        UserId userId;
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destSlot;
        UINT8 destCount;
    };

    struct UserItemBankToBagIncoming
    {
        UINT16 opcode{ 0x705 };
        UserId userId;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destBag;
        UINT8 destSlot;
        UINT8 destCount;
    };

    struct UserItemBankToBankIncoming
    {
        UINT16 opcode{ 0x706 };
        UserId userId;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destSlot;
        UINT8 destCount;
    };

    struct UserItemCountIncoming
    {
        UINT16 opcode{ 0x707 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };

    struct UserItemQualityIncoming
    {
        UINT16 opcode{ 0x70C };
        UserId userId;
        // 0:12
        UINT8 equipmentSlot;
        UINT16 quality;
    };

    struct UserItemCraftNameIncoming
    {
        UINT16 opcode{ 0x717 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;
    };
    #pragma pack(pop)
}