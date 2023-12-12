#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserItem

namespace shaiya
{
    #pragma pack(push, 1)
    // inventory
    struct UserItemRemoveIncoming
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

    struct UserItemQualityIncoming
    {
        UINT16 opcode{ 0x70C };
        UserId userId;
        // 0:12
        UINT8 equipmentSlot;
        UINT16 quality;
    };

    // aka bank teller
    struct UserItemBoxToBagIncoming
    {
        UINT16 opcode{ 0x710 };
        UserId userId;
        UINT8 srcSlot;
        UINT8 destBag;
        UINT8 destSlot;
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