#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item0D29
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };

    struct GuildBankItemListOutgoing
    {
        UINT16 opcode{ 0xD29 };
        UINT8 itemCount;
        Array<Item0D29, 50> itemList;
    };
    #pragma pack(pop)
}
