#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/BillingItemUnit.h>
#include <shaiya/include/network/game/BillingProductList.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_BILLING_ITEMLIST
    struct GameBillingItemListOutgoing
    {
        uint16_t opcode{ 0xB101 };
        uint8_t itemCount;
        Array<BillingItemUnit, 240> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_BILLING_ITEMGET
    struct GameBillingItemGetOutgoing
    {
        uint16_t opcode{ 0xB102 };
        uint8_t npcSlot;
        uint8_t bag;
        uint8_t slot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_BILLING_SERVICETYPE
    struct GameBillingServiceTypeOutgoing
    {
        uint16_t opcode{ 0xB103 };
        uint8_t serviceType;
        time32_t expireTime;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_BILLING_LOGOFFTIME
    struct GameBillingLogoutTimeOutgoing
    {
        uint16_t opcode{ 0xB105 };
        time32_t time;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_BILLING_PRODUCTLIST
    struct GameBillingProductListOutgoing
    {
        uint16_t opcode{ 0xB106 };
        uint8_t itemCount;
        Array<BillingProductList, 128> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
