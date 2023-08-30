#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemRuneCombineResult : UINT8
    {
        Success,
        NotImplemented,
        Failure
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
