#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

// CUser::PacketGem

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemCloakBadgeOutgoing
    {
        UINT16 opcode{ 0x803 };
        bool success;
        UINT8 bag;
        UINT8 slot;
        UINT8 frontPattern;
        UINT8 backPattern;
        UINT8 emblem;
        UINT8 frontPatternColor;
        UINT8 backPatternColor;
        UINT8 emblemColor;
        UINT32 money;

        ItemCloakBadgeOutgoing() = default;

        ItemCloakBadgeOutgoing(bool success, UINT8 bag, UINT8 slot, const CloakBadge& badge, UINT32 money)
            : success(success), bag(bag), slot(slot), money(money)
        {
            this->frontPattern = badge[0];
            this->backPattern = badge[1];
            this->emblem = badge[2];
            this->frontPatternColor = badge[3];
            this->backPatternColor = badge[4];
            this->emblemColor = badge[5];
        }
    };
    #pragma pack(pop)

    enum struct ItemLapisianAddResult : UINT8
    {
        Failure,
        Success
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
            UINT8 materialBag, UINT8 materialSlot, UINT8 materialCount, UINT8 itemBag, UINT8 itemSlot, 
            UINT32 money, const CraftName& craftName
        )
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

    enum struct ItemComposeResult : UINT8
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct ItemComposeOutgoing
    {
        UINT16 opcode{ 0x806 };
        ItemComposeResult result;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;

        ItemComposeOutgoing() = default;

        ItemComposeOutgoing(ItemComposeResult result, UINT8 bag, UINT8 slot, const CraftName& craftName)
            : result(result), bag(bag), slot(slot), craftName(craftName)
        {
        }
    };
    #pragma pack(pop)

    enum struct ItemRemakeResult : UINT8
    {
        Success,
        Failure,
        NotAllowed
    };

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

        ItemRemakeOutgoing() = default;

        ItemRemakeOutgoing(ItemRemakeResult result, UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId, UINT8 count,
            UINT16 quality, const Gems& gems, const CraftName& craftName
        )
        {
            this->result = result;
            this->bag = bag;
            this->slot = slot;
            this->type = type;
            this->typeId = typeId;
            this->count = count;
            this->quality = quality;
            this->gems = gems;
            this->craftName = craftName;
        }
    };
    #pragma pack(pop)

    enum struct ItemRemake2Result : UINT8
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct ItemRemake2Outgoing
    {
        UINT16 opcode{ 0x808 };
        ItemRemake2Result result;

        ItemRemake2Outgoing() = default;

        ItemRemake2Outgoing(ItemRemake2Result result)
            : result(result)
        {
        }
    };
    #pragma pack(pop)

    enum struct ItemLapisCombineResult : UINT8
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct ItemLapisCombineOutgoing
    {
        UINT16 opcode{ 0x80B };
        ItemLapisCombineResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;

        ItemLapisCombineOutgoing() = default;

        ItemLapisCombineOutgoing(ItemLapisCombineResult result, UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId, UINT8 count)
            : result(result), bag(bag), slot(slot), type(type), typeId(typeId), quality(0), gems{}, count(count), craftName{}
        {
        }
    };
    #pragma pack(pop)

    enum struct ItemLapisianCombineResult : UINT8
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    struct ItemLapisianCombineOutgoing
    {
        UINT16 opcode{ 0x80C };
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

    enum struct ItemRuneCombineResult : UINT8
    {
        Success,
        NotImplemented,
        Failure
    };

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

    enum struct ItemPerfectLapisianCombineResult : UINT8
    {
        Success,
        Unknown1,
        Unknown2,
        Unknown3,
    };

    #pragma pack(push, 1)
    struct ItemPerfectLapisianCombineOutgoing
    {
        UINT16 opcode{ 0x80E };
        ItemPerfectLapisianCombineResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;

        ItemPerfectLapisianCombineOutgoing() = default;

        ItemPerfectLapisianCombineOutgoing(ItemPerfectLapisianCombineResult result, UINT8 bag, UINT8 slot, UINT8 type, UINT8 typeId, UINT8 count)
            : result(result), bag(bag), slot(slot), type(type), typeId(typeId), quality(0), gems{}, count(count), craftName{}
        {
        }
    };
    #pragma pack(pop)

    enum struct ItemAbilityTransferResult : UINT8
    {
        Success,
        Failure
    };

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
        Array<UINT8, 10> createType;
        Array<UINT8, 10> createTypeId;
        UINT32 goldPerPercentage;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    #pragma pack(pop)

    enum struct ItemSynthesisResult : UINT8
    {
        Success = 1,
        Failure
    };

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
