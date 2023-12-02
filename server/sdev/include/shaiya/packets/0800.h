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
    #pragma pack(pop)
}
