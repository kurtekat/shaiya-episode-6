#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ServerTimeOutgoing
    {
        UINT16 opcode{ 0x115 };
        ULONG time;
    };
    #pragma pack(pop)
}
