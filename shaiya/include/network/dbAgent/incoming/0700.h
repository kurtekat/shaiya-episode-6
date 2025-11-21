#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_DB_ITEM_DROP
    struct DBAgentItemDropIncoming
    {
        uint16_t opcode{ 0x702 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_BAGTOBANK
    struct DBAgentItemBagToBankIncoming
    {
        uint16_t opcode{ 0x704 };
        uint32_t billingId;
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t srcCount;
        uint8_t destSlot;
        uint8_t destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_BANKTOBAG
    struct DBAgentItemBankToBagIncoming
    {
        uint16_t opcode{ 0x705 };
        uint32_t billingId;
        uint8_t srcSlot;
        uint8_t srcCount;
        uint8_t destBag;
        uint8_t destSlot;
        uint8_t destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_BANKTOBANK
    struct DBAgentItemBankToBankIncoming
    {
        uint16_t opcode{ 0x706 };
        uint32_t billingId;
        uint8_t srcSlot;
        uint8_t srcCount;
        uint8_t destSlot;
        uint8_t destCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_SET_COUNT
    struct DBAgentItemSetCountIncoming
    {
        uint16_t opcode{ 0x707 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_GEM_REMOVE
    struct DBAgentItemGemRemoveIncoming
    {
        uint16_t opcode{ 0x709 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        uint16_t quality;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_GEM_UPDATE
    struct DBAgentItemGemUpdateIncoming
    {
        uint16_t opcode{ 0x711 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        Gems gems;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_GEM_REMOVE_POS
    struct DBAgentItemGemRemovePosIncoming
    {
        uint16_t opcode{ 0x715 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        uint8_t gemPos;
        uint16_t quality;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_LAPISIAN_ADD
    struct DBAgentItemLapisianAddIncoming
    {
        uint16_t opcode{ 0x716 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        uint32_t money;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_ITEM_CRAFT_UPDATE
    struct DBAgentItemCraftUpdateIncoming
    {
        uint16_t opcode{ 0x717 };
        uint32_t billingId;
        uint8_t bag;
        uint8_t slot;
        CraftName craftName;
    };
    #pragma pack(pop)
}
