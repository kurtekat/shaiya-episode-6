#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/item/CraftName.h>
#include <shaiya/include/item/Gems.h>
#include <sdev/include/shaiya/include/CItem.h>
#include <sdev/include/shaiya/include/Synthesis.h>

// CUser::PacketGem

namespace shaiya
{
    enum struct ItemLapisianAddResult : UINT8
    {
        Failure,
        Success
    };

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

    enum struct ItemLapisianCombineResult : UINT8
    {
        Success,
        Unknown1,
        Unknown2,
        Unknown3,
    };

    enum struct ItemAbilityTransferResult : UINT8
    {
        Success,
        Failure
    };

    enum struct ItemSynthesisResult : UINT8
    {
        Success = 1,
        Failure
    };

    #pragma pack(push, 1)
    struct ItemLapisianAddOutgoing
    {
        UINT16 opcode{ 0x805 };
        ItemLapisianAddResult result;
        UINT8 lapisianBag;
        UINT8 lapisianSlot;
        UINT8 lapisianCount;
        UINT8 materialBag;
        UINT8 materialSlot;
        UINT8 materialCount;
        UINT8 itemBag;
        UINT8 itemSlot;
        UINT32 money;
        CraftName craftName;

        ItemLapisianAddOutgoing() = default;

        ItemLapisianAddOutgoing(ItemLapisianAddResult result, UINT8 lapisianBag, UINT8 lapisianSlot, UINT8 lapisianCount, 
            UINT8 materialBag, UINT8 materialSlot, UINT8 materialCount, UINT8 itemBag, UINT8 itemSlot, UINT32 money, CraftName& craftName)
        {
            this->result = result;
            this->lapisianBag = lapisianBag;
            this->lapisianSlot = lapisianSlot;
            this->lapisianCount = lapisianCount;
            this->materialBag = materialBag;
            this->materialSlot = materialSlot;
            this->materialCount = materialCount;
            this->itemBag = itemBag;
            this->itemSlot = itemSlot;
            this->money = money;
            this->craftName = craftName;
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemComposeOutgoing
    {
        UINT16 opcode{ 0x806 };
        ItemComposeResult result;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;

        ItemComposeOutgoing() = default;

        ItemComposeOutgoing(ItemComposeResult result, UINT8 bag, UINT8 slot, CraftName& craftName)
            : result(result), bag(bag), slot(slot), craftName(craftName)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    #pragma pack(push, 1)
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

        ItemRuneCombineOutgoing() = default;

        ItemRuneCombineOutgoing(ItemRuneCombineResult result, UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId, UINT8 count)
            : result(result), bag(bag), slot(slot), type(type), typeId(typeId), quality(0), gems{}, count(count), craftName{}
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemLapisianCombineOutgoing
    {
        UINT16 opcode{ 0x80E };
        ItemLapisianCombineResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;

        ItemLapisianCombineOutgoing() = default;

        ItemLapisianCombineOutgoing(ItemLapisianCombineResult result, UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId, UINT8 count)
            : result(result), bag(bag), slot(slot), type(type), typeId(typeId), quality(0), gems{}, count(count), craftName{}
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemAbilityTransferOutgoing
    {
        UINT16 opcode{ 0x811 };
        ItemAbilityTransferResult result;
        UINT8 fromBag;
        UINT8 fromSlot;
        UINT8 toBag;
        UINT8 toSlot;

        ItemAbilityTransferOutgoing() = default;

        ItemAbilityTransferOutgoing(ItemAbilityTransferResult result, UINT8 fromBag, UINT8 fromSlot, UINT8 toBag, UINT8 toSlot)
            : result(result), fromBag(fromBag), fromSlot(fromSlot), toBag(toBag), toSlot(toSlot)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemSynthesisListOutgoing
    {
        UINT16 opcode{ 0x830 };
        std::array<UINT8, 10> createType;
        std::array<UINT8, 10> createTypeId;
        UINT32 goldPerPercentage;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemSynthesisMaterialOutgoing
    {
        UINT16 opcode{ 0x831 };
        // e.g. 10000 = 100%
        UINT32 successRate;
        std::array<UINT8, 24> materialType;
        UINT8 createType;
        std::array<UINT8, 24> materialTypeId;
        UINT8 createTypeId;
        std::array<UINT8, 24> materialCount;
        UINT8 createCount;

        ItemSynthesisMaterialOutgoing() = default;

        ItemSynthesisMaterialOutgoing(Synthesis& synthesis)
            : successRate(0), materialType{}, createType(0), materialTypeId{}, createTypeId(0), materialCount{}, createCount(0)
        {
            this->successRate = synthesis.successRate;
            this->materialType = synthesis.materialType;
            this->createType = synthesis.createType;
            this->materialTypeId = synthesis.materialTypeId;
            this->createTypeId = synthesis.createTypeId;
            this->materialCount = synthesis.materialCount;
            this->createCount = synthesis.createCount;
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemSynthesisOutgoing
    {
        UINT16 opcode{ 0x832 };
        ItemSynthesisResult result;

        ItemSynthesisOutgoing() = default;

        ItemSynthesisOutgoing(ItemSynthesisResult result)
            : result(result)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemFreeSynthesisOutgoing
    {
        UINT16 opcode{ 0x833 };
        ItemSynthesisResult result;

        ItemFreeSynthesisOutgoing() = default;

        ItemFreeSynthesisOutgoing(ItemSynthesisResult result)
            : result(result)
        {
        }
    };
    #pragma pack(pop)
}
