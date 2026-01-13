#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
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
        Failure_MakeTypeQ,
        Failure_MakeTypeB,
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

    #pragma pack(push, 1)
    struct GameItemRemake2Outgoing
    {
        uint16_t opcode{ 0x808 };
        GameItemRemakeResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ItemRemake5
    // cuser__packetgem_protocol_itemget_compose
    struct GameItemGemComposeOutgoing
    {
        uint16_t opcode{ 0x80B };
        GameItemRemakeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ItemRemake4
    // cuser__packetgem_protocol_itemlapisian_compose
    struct GameItemLapisianComposeOutgoing
    {
        uint16_t opcode{ 0x80C };
        GameItemRemakeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameUpperRuneComposeResult : uint8_t
    {
        Success,
        NotImplemented,
        Failure
    };

    #pragma pack(push, 1)
    // cuser__packetgem_protocol_upperrune_compose
    struct GameUpperRuneComposeOutgoing
    {
        uint16_t opcode{ 0x80D };
        GameUpperRuneComposeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameItemLapisianRemakeResult : uint8_t
    {
        Success,
        Failure = 3,
    };

    #pragma pack(push, 1)
    // cuser__process_itemlapisian_remake
    struct GameItemLapisianRemakeOutgoing
    {
        uint16_t opcode{ 0x80E };
        GameItemLapisianRemakeResult result;
        ItemUnit newItem;
    };
    #pragma pack(pop)

    enum struct GameItemAbilityMoveResult : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct GameItemAbilityMoveOutgoing
    {
        uint16_t opcode{ 0x811 };
        GameItemAbilityMoveResult result;
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t destBag;
        uint8_t destSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChaoticSquareResultItemListOutgoing
    {
        uint16_t opcode{ 0x830 };
        Array<uint8_t, 10> resultItemType;
        Array<uint8_t, 10> resultItemTypeId;
        uint32_t fortuneMoney;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChaoticSquareRecipeOutgoing
    {
        uint16_t opcode{ 0x831 };
        uint32_t chance;
        Array<uint8_t, 24> materialType;
        uint8_t resultItemType;
        Array<uint8_t, 24> materialTypeId;
        uint8_t resultItemTypeId;
        Array<uint8_t, 24> materialCount;
        uint8_t resultItemCount;
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
