#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CashPointIncoming
    {
        UINT16 opcode{ 0x2605 };
    };

    struct CashPointOutgoing
    {
        UINT16 opcode{ 0x2605 };
        UINT32 points;
    };
    #pragma pack(pop)
}
