#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct PvPRequestIncoming
    {
        UINT16 opcode{ 0x2401 };
        CharId senderId;
    };

    struct PvPRequestOutgoing
    {
        UINT16 opcode{ 0x2401 };
        CharId senderId;
        CharId targetId;
    };
    #pragma pack(pop)
}
