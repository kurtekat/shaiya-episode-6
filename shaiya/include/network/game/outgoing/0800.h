#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/network/game/ItemUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_CLOAK_ADD
    struct GameCloakInfoAddOutgoing
    {
        uint16_t opcode{ 0x803 };
        bool success;
        uint8_t bag;
        uint8_t slot;
        CloakInfo cloakInfo;
        uint32_t money;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CLOAK_REM
    struct GameCloakInfoRemoveOutgoing
    {
        uint16_t opcode{ 0x804 };
        uint8_t bag;
        uint8_t slot;
    };
    #pragma pack(pop)

    enum struct GameLapisianAddResult : uint8_t
    {
        Failure,
        Success
    };

    #pragma pack(push, 1)
    // TP_LAPISIAN_ADD
    struct GameLapisianAddOutgoing
    {
        uint16_t opcode{ 0x805 };
        GameLapisianAddResult result;
        uint8_t lapisianBag;
        uint8_t lapisianSlot;
        uint8_t lapisianCount;
        uint8_t materialBag;
        uint8_t materialSlot;
        uint8_t materialCount;
        uint8_t itemBag;
        uint8_t itemSlot;
        uint32_t money;
        CraftName craftName;
    };
    #pragma pack(pop)

    enum struct GameItemComposeResult : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    // TP_ITEM_COMPOSE
    struct GameItemComposeOutgoing
    {
        uint16_t opcode{ 0x806 };
        GameItemComposeResult result;
        uint8_t bag;
        uint8_t slot;
        CraftName craftName;
    };
    #pragma pack(pop)

    enum struct GameItemRemakeResult : uint8_t
    {
        Success,
        Failure,
        NotAllowed
    };

    #pragma pack(push, 1)
    // TPC_ITEM_REMAKE
    struct GameItemRemakeOutgoing
    {
        uint16_t opcode{ 0x807 };
        GameItemRemakeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameItemRemake2Result : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct GameItemRemake2Outgoing
    {
        uint16_t opcode{ 0x808 };
        GameItemRemake2Result result;
    };
    #pragma pack(pop)

    enum struct GameItemRemake5Result : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct GameItemRemake5Outgoing
    {
        uint16_t opcode{ 0x80B };
        GameItemRemake5Result result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameItemRemake4Result : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct GameItemRemake4Outgoing
    {
        uint16_t opcode{ 0x80C };
        GameItemRemake4Result result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameRuneUpgradeResult : uint8_t
    {
        Success,
        NotImplemented,
        Failure
    };

    #pragma pack(push, 1)
    struct GameRuneUpgradeOutgoing
    {
        uint16_t opcode{ 0x80D };
        GameRuneUpgradeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameLapisianUpgradeResult : uint8_t
    {
        Success,
        Unknown1,
        Unknown2,
        Unknown3,
    };

    #pragma pack(push, 1)
    struct GameLapisianUpgradeOutgoing
    {
        uint16_t opcode{ 0x80E };
        GameLapisianUpgradeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameItemAbilityTransferResult : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct GameItemAbilityTransferOutgoing
    {
        uint16_t opcode{ 0x811 };
        GameItemAbilityTransferResult result;
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t destBag;
        uint8_t destSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemSynthesisListOutgoing
    {
        uint16_t opcode{ 0x830 };
        Array<uint8_t, 10> createType;
        Array<uint8_t, 10> createTypeId;
        uint32_t goldPerPercentage;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemSynthesisMaterialOutgoing
    {
        uint16_t opcode{ 0x831 };
        // e.g. 10000 = 100%
        uint32_t successRate;
        Array<uint8_t, 24> materialType;
        uint8_t createType;
        Array<uint8_t, 24> materialTypeId;
        uint8_t createTypeId;
        Array<uint8_t, 24> materialCount;
        uint8_t createCount;
    };
    #pragma pack(pop)

    enum struct GameItemSynthesisResult : uint8_t
    {
        Success = 1,
        Failure
    };

    #pragma pack(push, 1)
    struct GameItemSynthesisOutgoing
    {
        uint16_t opcode{ 0x832 };
        GameItemSynthesisResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemFreeSynthesisOutgoing
    {
        uint16_t opcode{ 0x833 };
        GameItemSynthesisResult result;
    };
    #pragma pack(pop)
}
