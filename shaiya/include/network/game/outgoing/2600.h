#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/PointItemUnit.h>
#include <shaiya/include/network/game/PointLogUnit.h>
#include <shaiya/include/network/game/PointStoredItemUnit.h>

namespace shaiya
{
    enum struct GamePointBuyResult : uint8_t
    {
        Success,
        ProductCodeDoesNotExist,
        NotEnoughPoints,
        NotEnoughSlots
    };

    #pragma pack(push, 1)
    // TP_POINT_BUY
    template<class PointItemUnitT>
    struct GamePointBuyOutgoing
    {
        uint16_t opcode{ 0x2602 };
        GamePointBuyResult result;
        uint32_t remainingPoints;
        PointLogUnit log;
        uint8_t itemCount;
        Array<PointItemUnitT, 24> itemList;

        constexpr static int baseLength = 37;
    };
    #pragma pack(pop)

    enum struct GamePointGiftSendResult : uint8_t
    {
        Success,
        CharNameDoesNotExist,
        SameAccount,
        Full,
        NotEnoughSlots,
        InsertError,
        ProductCodeDoesNotExist,
        PointUpdateError,
        LogError,
        ProcessBusy,
        NotEnoughPoints
    };

    #pragma pack(push, 1)
    // TP_POINT_GIFT_SEND
    struct GamePointGiftSendOutgoing
    {
        uint16_t opcode{ 0x2603 };
        GamePointGiftSendResult result;
        String<21> targetName;
        uint32_t remainingPoints;
        PointLogUnit log;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamePointOutgoing
    {
        uint16_t opcode{ 0x2605 };
        uint32_t points;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_POINT_STORED_ITEMLIST
    struct GamePointStoredItemListOutgoing
    {
        uint16_t opcode{ 0x2606 };
        uint8_t itemCount;
        Array<PointStoredItemUnit, 240> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_POINT_STORED_ITEMGET
    struct GamePointStoredItemGetOutgoing
    {
        uint16_t opcode{ 0x2607 };
        uint8_t npcSlot;
        uint8_t bag;
        uint8_t slot;
    };
    #pragma pack(pop)
}
