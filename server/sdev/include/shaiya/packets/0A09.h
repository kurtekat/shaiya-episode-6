#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExchangeItemOutgoing
    {
        UINT16 opcode{ 0xA09 };
        UINT8 destSlot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        #ifdef WITH_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)
}
