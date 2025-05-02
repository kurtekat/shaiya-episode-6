#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_DB_POINT_ITEM_GIFT_SEND
    struct DBAgentPointItemGiftSendIncoming
    {
        uint16_t opcode{ 0xE03 };
        uint32_t billingId;
        String<21> targetName;
        String<21> productCode;
        uint32_t purchasePoints;
        time32_t purchaseDate;
        uint32_t purchaseNumber;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_DB_POINT_RELOAD
    struct DBAgentPointReloadIncoming
    {
        uint16_t opcode{ 0xE06 };
        uint32_t billingId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPointUpdateIncoming
    {
        uint16_t opcode{ 0xE0A };
        uint32_t billingId;
    };
    #pragma pack(pop)
}
