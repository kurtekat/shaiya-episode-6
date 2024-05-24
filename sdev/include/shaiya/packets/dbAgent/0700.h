#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserItem

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserItemCreateIncoming
    {
        UINT16 opcode{ 0x701 };
        UserId userId;
        UINT64 uniqueId;
        UINT32 itemId;
        UINT8 bag;
        UINT8 slot;
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
    // inventory
    struct UserItemRemoveIncoming
    {
        UINT16 opcode{ 0x702 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemBankToBankIncoming
    {
        UINT16 opcode{ 0x706 };
        UserId userId;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destSlot;
        UINT8 destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemCountIncoming
    {
        UINT16 opcode{ 0x707 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemGemRemoveAllIncoming
    {
        UINT16 opcode{ 0x709 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT16 quality;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemQualityIncoming
    {
        UINT16 opcode{ 0x70C };
        UserId userId;
        // 0:12
        UINT8 equipmentSlot;
        UINT16 quality;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemGemsIncoming
    {
        UINT16 opcode{ 0x711 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        Gems gems;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemGemRemovePosIncoming
    {
        UINT16 opcode{ 0x715 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 gemPos;
        UINT16 quality;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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