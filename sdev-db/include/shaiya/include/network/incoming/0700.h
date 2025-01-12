#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

// CUser::PacketUserItem

namespace shaiya
{
    #pragma pack(push, 1)
    // inventory
    struct DBAgentItemRemoveIncoming
    {
        UINT16 opcode{ 0x702 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemBagToBankIncoming
    {
        UINT16 opcode{ 0x704 };
        ULONG userId;
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destSlot;
        UINT8 destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemBankToBagIncoming
    {
        UINT16 opcode{ 0x705 };
        ULONG userId;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destBag;
        UINT8 destSlot;
        UINT8 destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemBankToBankIncoming
    {
        UINT16 opcode{ 0x706 };
        ULONG userId;
        UINT8 srcSlot;
        UINT8 srcCount;
        UINT8 destSlot;
        UINT8 destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemCountIncoming
    {
        UINT16 opcode{ 0x707 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemGemRemoveAllIncoming
    {
        UINT16 opcode{ 0x709 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        UINT16 quality;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemGemsIncoming
    {
        UINT16 opcode{ 0x711 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        Gems gems;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemGemRemovePosIncoming
    {
        UINT16 opcode{ 0x715 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        UINT8 gemPos;
        UINT16 quality;
        UINT32 money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemEnchantIncoming
    {
        UINT16 opcode{ 0x716 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        UINT32 money;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentItemCraftNameIncoming
    {
        UINT16 opcode{ 0x717 };
        ULONG userId;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;
    };
    #pragma pack(pop)
}