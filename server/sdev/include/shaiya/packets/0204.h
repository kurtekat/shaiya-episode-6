#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item0204
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
    };

    struct ItemMove
    {
        UINT16 opcode{ 0x204 };
        Item0204 srcItem;
        Item0204 destItem;
    };
    #pragma pack(pop)
}
