#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_CLOAK_ADD
    struct GameCloakInfoIncoming
    {
        uint16_t opcode{ 0x803 };
        uint8_t bag;
        uint8_t slot;
        CloakInfo cloakInfo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_LAPISIAN_ADD
    struct GameLapisianAddIncoming_EP5
    {
        uint16_t opcode{ 0x805 };
        uint8_t lapisianBag;
        uint8_t lapisianSlot;
        uint8_t materialBag;
        uint8_t materialSlot;
        uint8_t materialCount;
        uint8_t itemBag;
        uint8_t itemSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_LAPISIAN_ADD
    struct GameLapisianAddIncoming_EP6
    {
        uint16_t opcode{ 0x805 };
        uint8_t lapisianBag;
        uint8_t lapisianSlot;
        uint8_t materialBag;
        uint8_t materialSlot;
        uint8_t materialCount;
        uint8_t itemBag;
        uint8_t itemSlot;
        bool itemProtect;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_LAPISIAN_ADD
    struct GameLapisianAddIncoming_EP6_4
    {
        uint16_t opcode{ 0x805 };
        uint8_t lapisianBag;
        uint8_t lapisianSlot;
        uint8_t materialBag;
        uint8_t materialSlot;
        uint8_t materialCount;
        uint8_t itemBag;
        uint8_t itemSlot;
        bool itemProtect;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_ITEM_COMPOSE
    struct GameItemComposeIncoming_EP5
    {
        uint16_t opcode{ 0x806 };
        uint8_t runeBag;
        uint8_t runeSlot;
        uint8_t itemBag;
        uint8_t itemSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_ITEM_COMPOSE
    struct GameItemComposeIncoming_EP6_4
    {
        uint16_t opcode{ 0x806 };
        uint8_t runeBag;
        uint8_t runeSlot;
        uint8_t itemBag;
        uint8_t itemSlot;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_ITEM_REMAKE
    struct GameItemRemakeIncoming_EP5
    {
        uint16_t opcode{ 0x807 };
        uint8_t bag1;
        uint8_t bag2;
        uint8_t bag3;
        uint8_t slot1;
        uint8_t slot2;
        uint8_t slot3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_ITEM_REMAKE
    struct GameItemRemakeIncoming_EP6_4
    {
        uint16_t opcode{ 0x807 };
        uint8_t bag1;
        uint8_t bag2;
        uint8_t bag3;
        uint8_t slot1;
        uint8_t slot2;
        uint8_t slot3;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemRemake2Incoming
    {
        uint16_t opcode{ 0x808 };
        uint8_t bag;
        uint8_t slot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemRemake5Incoming_EP5
    {
        uint16_t opcode{ 0x80B };
        uint8_t lapisBag1;
        uint8_t lapisBag2;
        uint8_t lapisBag3;
        uint8_t lapisSlot1;
        uint8_t lapisSlot2;
        uint8_t lapisSlot3;
        uint8_t vialBag;
        uint8_t vialSlot;
        uint8_t vialCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemRemake5Incoming_EP6_4
    {
        uint16_t opcode{ 0x80B };
        uint8_t lapisBag1;
        uint8_t lapisBag2;
        uint8_t lapisBag3;
        uint8_t lapisSlot1;
        uint8_t lapisSlot2;
        uint8_t lapisSlot3;
        uint8_t vialBag;
        uint8_t vialSlot;
        uint8_t vialCount;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemRemake4Incoming_EP5
    {
        uint16_t opcode{ 0x80C };
        uint8_t lapisianBag1;
        uint8_t lapisianBag2;
        uint8_t lapisianBag3;
        uint8_t lapisianSlot1;
        uint8_t lapisianSlot2;
        uint8_t lapisianSlot3;
        uint8_t vialBag;
        uint8_t vialSlot;
        uint8_t vialCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemRemake4Incoming_EP6_4
    {
        uint16_t opcode{ 0x80C };
        uint8_t lapisianBag1;
        uint8_t lapisianBag2;
        uint8_t lapisianBag3;
        uint8_t lapisianSlot1;
        uint8_t lapisianSlot2;
        uint8_t lapisianSlot3;
        uint8_t vialBag;
        uint8_t vialSlot;
        uint8_t vialCount;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
    struct GameRuneUpgradeIncoming_EP5
    {
        uint16_t opcode{ 0x80D };
        uint8_t runeBag;
        uint8_t runeSlot;
        uint8_t vialBag;
        uint8_t vialSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameRuneUpgradeIncoming_EP6_4
    {
        uint16_t opcode{ 0x80D };
        uint8_t runeBag;
        uint8_t runeSlot;
        uint8_t vialBag;
        uint8_t vialSlot;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameLapisianUpgradeIncoming
    {
        uint16_t opcode{ 0x80E };
        uint8_t cubeBag;
        uint8_t cubeSlot;
        uint8_t lapisianType;
        uint8_t lapisianTypeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemAbilityTransferIncoming
    {
        uint16_t opcode{ 0x811 };
        uint8_t cubeBag;
        uint8_t cubeSlot;
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t destBag;
        uint8_t destSlot;
        uint8_t catalystBag;
        uint8_t catalystSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameChaoticSquareListIncoming
    {
        uint16_t opcode{ 0x830 };
        uint8_t chaoticSquareBag;
        uint8_t chaoticSquareSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemSynthesisRecipeIncoming
    {
        uint16_t opcode{ 0x831 };
        uint8_t newItemType;
        uint8_t newItemTypeId;
        uint32_t index;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemSynthesisIncoming
    {
        uint16_t opcode{ 0x832 };
        uint8_t chaoticSquareBag;
        uint8_t chaoticSquareSlot;
        uint32_t money;
        uint32_t index;
        uint8_t hammerBag;
        uint8_t hammerSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemFreeSynthesisIncoming
    {
        uint16_t opcode{ 0x833 };
        uint8_t chaoticSquareBag;
        uint8_t chaoticSquareSlot;
        uint32_t money;
        uint8_t hammerBag;
        uint8_t hammerSlot;
        Array<uint8_t, 24> materialType;
        Array<uint8_t, 24> materialTypeId;
        Array<uint8_t, 24> materialCount;
    };
    #pragma pack(pop)
}
