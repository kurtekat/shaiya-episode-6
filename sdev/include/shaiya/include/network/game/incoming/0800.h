#pragma once
#include <shaiya/include/common.h>

// CUser::PacketGem

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemCloakBadgeIncoming
    {
        UINT16 opcode{ 0x803 };
        UINT8 bag;
        UINT8 slot;
        UINT8 frontPattern;
        UINT8 backPattern;
        UINT8 emblem;
        UINT8 frontPatternColor;
        UINT8 backPatternColor;
        UINT8 emblemColor;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisianAddIncoming_EP5
    {
        UINT16 opcode{ 0x805 };
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 materialBag;
        UINT8 materialSlot;
        UINT8 materialCount;
        UINT8 itemBag;
        UINT8 itemSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisianAddIncoming_EP6
    {
        UINT16 opcode{ 0x805 };
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 materialBag;
        UINT8 materialSlot;
        UINT8 materialCount;
        UINT8 itemBag;
        UINT8 itemSlot;
        bool safetyCharm;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisianAddIncoming_EP6_4
    {
        UINT16 opcode{ 0x805 };
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 materialBag;
        UINT8 materialSlot;
        UINT8 materialCount;
        UINT8 itemBag;
        UINT8 itemSlot;
        bool safetyCharm;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemComposeIncoming_EP5
    {
        UINT16 opcode{ 0x806 };
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 itemBag;
        UINT8 itemSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemComposeIncoming_EP6_4
    {
        UINT16 opcode{ 0x806 };
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 itemBag;
        UINT8 itemSlot;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemakeIncoming_EP5
    {
        UINT16 opcode{ 0x807 };
        UINT8 bag1;
        UINT8 bag2;
        UINT8 bag3;
        UINT8 slot1;
        UINT8 slot2;
        UINT8 slot3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemakeIncoming_EP6_4
    {
        UINT16 opcode{ 0x807 };
        UINT8 bag1;
        UINT8 bag2;
        UINT8 bag3;
        UINT8 slot1;
        UINT8 slot2;
        UINT8 slot3;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemake2Incoming
    {
        UINT16 opcode{ 0x808 };
        UINT8 bag;
        UINT8 slot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisCombineIncoming_EP5
    {
        UINT16 opcode{ 0x80B };
        UINT8 lapisBag1;
        UINT8 lapisBag2;
        UINT8 lapisBag3;
        UINT8 lapisSlot1;
        UINT8 lapisSlot2;
        UINT8 lapisSlot3;
        UINT8 essenceBag;
        UINT8 essenceSlot;
        UINT8 essenceCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisCombineIncoming_EP6_4
    {
        UINT16 opcode{ 0x80B };
        UINT8 lapisBag1;
        UINT8 lapisBag2;
        UINT8 lapisBag3;
        UINT8 lapisSlot1;
        UINT8 lapisSlot2;
        UINT8 lapisSlot3;
        UINT8 essenceBag;
        UINT8 essenceSlot;
        UINT8 essenceCount;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisianCombineIncoming_EP5
    {
        UINT16 opcode{ 0x80C };
        UINT8 lapisianBag1;
        UINT8 lapisianBag2;
        UINT8 lapisianBag3;
        UINT8 lapisianSlot1;
        UINT8 lapisianSlot2;
        UINT8 lapisianSlot3;
        UINT8 liquidBag;
        UINT8 liquidSlot;
        UINT8 liquidCount;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisianCombineIncoming_EP6_4
    {
        UINT16 opcode{ 0x80C };
        UINT8 lapisianBag1;
        UINT8 lapisianBag2;
        UINT8 lapisianBag3;
        UINT8 lapisianSlot1;
        UINT8 lapisianSlot2;
        UINT8 lapisianSlot3;
        UINT8 liquidBag;
        UINT8 liquidSlot;
        UINT8 liquidCount;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // not implemented
    struct ItemRuneCombineIncoming_EP5
    {
        UINT16 opcode{ 0x80D };
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 vialBag;
        UINT8 vialSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRuneCombineIncoming_EP6_4
    {
        UINT16 opcode{ 0x80D };
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 vialBag;
        UINT8 vialSlot;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemPerfectLapisianCombineIncoming
    {
        UINT16 opcode{ 0x80E };
        UINT8 cubeBag;
        UINT8 cubeSlot;
        UINT8 lapisianType;
        UINT8 lapisianTypeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemAbilityTransferIncoming
    {
        UINT16 opcode{ 0x811 };
        UINT8 cubeBag;
        UINT8 cubeSlot;
        UINT8 fromBag;
        UINT8 fromSlot;
        UINT8 toBag;
        UINT8 toSlot;
        UINT8 catalystBag;
        UINT8 catalystSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemSynthesisListIncoming
    {
        UINT16 opcode{ 0x830 };
        UINT8 squareBag;
        UINT8 squareSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemSynthesisMaterialIncoming
    {
        UINT16 opcode{ 0x831 };
        UINT8 createType;
        UINT8 createTypeId;
        UINT32 index;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemSynthesisIncoming
    {
        UINT16 opcode{ 0x832 };
        UINT8 squareBag;
        UINT8 squareSlot;
        UINT32 money;
        UINT32 index;
        UINT8 hammerBag;
        UINT8 hammerSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemFreeSynthesisIncoming
    {
        UINT16 opcode{ 0x833 };
        UINT8 squareBag;
        UINT8 squareSlot;
        UINT32 money;
        UINT8 hammerBag;
        UINT8 hammerSlot;
        Array<UINT8, 24> materialType;
        Array<UINT8, 24> materialTypeId;
        Array<UINT8, 24> materialCount;
    };
    #pragma pack(pop)
}
