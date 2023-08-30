#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BlockRemoveIncoming
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;
    };

    struct BlockRemoveOutgoing
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;
    };
    #pragma pack(pop)
}
