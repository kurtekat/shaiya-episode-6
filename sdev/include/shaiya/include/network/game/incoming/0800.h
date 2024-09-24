#pragma once
#include <shaiya/include/common.h>

// CUser::PacketGem

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemCloakBadgeCombineIncoming
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
    struct ItemLapisianAddIncoming
    {
        UINT16 opcode{ 0x805 };
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 materialBag;
        UINT8 materialSlot;
        UINT8 materialCount;
        UINT8 itemBag;
        UINT8 itemSlot;
        // EP6
        bool safetyCharm;
        // EP6.4
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemComposeIncoming
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
    struct ItemRemakeIncoming
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
    struct ItemRuneCombineIncoming
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
    struct ItemLapisianCombineIncoming
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
