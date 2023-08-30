#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    enum struct BlockAddResult : UINT8
    {
        Failure,
        Success
    };

    #pragma pack(push, 1)
    struct BlockAddResultOutgoing
    {
        UINT16 opcode{ 0x220E };
        BlockAddResult result;
    };
    #pragma pack(pop)
}
