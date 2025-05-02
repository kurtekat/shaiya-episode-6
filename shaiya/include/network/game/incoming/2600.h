#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_POINT_BUY
    struct GamePointBuyIncoming
    {
        uint16_t opcode{ 0x2602 };
        String<21> productCode;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_POINT_GIFT_SEND
    struct GamePointGiftSendIncoming
    {
        uint16_t opcode{ 0x2603 };
        String<21> productCode;
        String<21> targetName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamePointRequest
    {
        uint16_t opcode{ 0x2605 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_POINT_STORED_ITEMGET
    struct GamePointStoredItemGetIncoming
    {
        uint16_t opcode{ 0x2607 };
        uint8_t npcSlot;
    };
    #pragma pack(pop)
}
