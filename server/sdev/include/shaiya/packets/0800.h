#pragma once
#include <include/shaiya/common.h>

// CUser::PacketGem

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemComposeResult : UINT8
    {
        Success,
        Failure
    };

    enum struct ItemRemakeResult : UINT8
    {
        Success,
        Failure,
        NotAllowed
    };

    enum struct ItemRuneCombineResult : UINT8
    {
        Success,
        NotImplemented,
        Failure
    };

    enum struct ItemSynthesisResult : UINT8
    {
        Success = 1,
        Failure
    };

    struct ItemLapisianAddIncoming
    {
        UINT16 opcode{ 0x805 };
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 enchantItemBag;
        UINT8 enchantItemSlot;
        UINT8 enchantItemCount;
        UINT8 upgradeItemBag;
        UINT8 upgradeItemSlot;
        UINT8 unknown;
        ULONG npcId;
    };

    struct ItemComposeIncoming
    {
        UINT16 opcode{ 0x806 };
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 itemBag;
        UINT8 itemSlot;
        ULONG npcId;
    };

    struct ItemComposeOutgoing
    {
        UINT16 opcode{ 0x806 };
        ItemComposeResult result;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;
    };

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

    struct ItemRemakeOutgoing
    {
        UINT16 opcode{ 0x807 };
        ItemRemakeResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };

    struct ItemRuneCombineIncoming
    {
        UINT16 opcode{ 0x80D };
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 vialBag;
        UINT8 vialSlot;
        ULONG npcId;
    };

    struct ItemRuneCombineOutgoing
    {
        UINT16 opcode{ 0x80D };
        ItemRuneCombineResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };

    struct ItemSynthesisListIncoming
    {
        UINT16 opcode{ 0x830 };
        UINT8 squareBag;
        UINT8 squareSlot;
    };

    struct ItemSynthesisListOutgoing
    {
        UINT16 opcode{ 0x830 };
        Array<UINT8, 10> createType;
        Array<UINT8, 10> createTypeId;
        UINT32 goldPerPercentage;
    };

    struct ItemSynthesisMaterialIncoming
    {
        UINT16 opcode{ 0x831 };
        UINT8 createType;
        UINT8 createTypeId;
        UINT32 index;
    };

    struct ItemSynthesisMaterialOutgoing
    {
        UINT16 opcode{ 0x831 };
        // e.g. 10000 = 100%
        UINT32 successRate;
        Array<UINT8, 24> materialType;
        UINT8 createType;
        Array<UINT8, 24> materialTypeId;
        UINT8 createTypeId;
        Array<UINT8, 24> materialCount;
        UINT8 createCount;
    };

    struct ItemSynthesisIncoming
    {
        UINT16 opcode{ 0x832 };
        UINT8 squareBag;
        UINT8 squareSlot;
        // 0:5000
        UINT32 money;
        UINT32 index;
        UINT8 hammerBag;
        UINT8 hammerSlot;
    };

    struct ItemSynthesisOutgoing
    {
        UINT16 opcode{ 0x832 };
        ItemSynthesisResult result;
    };

    struct ItemFreeSynthesisIncoming
    {
        UINT16 opcode{ 0x833 };
        UINT8 squareBag;
        UINT8 squareSlot;
        // 0:5000
        UINT32 money;
        UINT8 hammerBag;
        UINT8 hammerSlot;
        Array<UINT8, 24> materialType;
        Array<UINT8, 24> materialTypeId;
        Array<UINT8, 24> materialCount;
    };

    struct ItemFreeSynthesisOutgoing
    {
        UINT16 opcode{ 0x833 };
        ItemSynthesisResult result;
    };
    #pragma pack(pop)
}
