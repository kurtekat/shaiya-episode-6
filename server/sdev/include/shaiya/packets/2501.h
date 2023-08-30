#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GvGRequestIncoming
    {
        UINT16 opcode{ 0x2501 };
        CharId senderId;
    };

    struct GvGRequestOutgoing
    {
        UINT16 opcode{ 0x2501 };
        CharId senderId;
        CharId targetId;
    };
    #pragma pack(pop)
}
