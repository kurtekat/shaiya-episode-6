#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemDuration
    {
        UINT16 opcode{ 0x22E };
        UINT8 bag;
        UINT8 slot;
        ULONG fromDate;
        ULONG toDate;
        ULONG unknown;
    };
    #pragma pack(pop)
}
