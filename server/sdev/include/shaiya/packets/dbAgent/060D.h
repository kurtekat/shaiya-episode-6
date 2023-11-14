#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveGrowIncoming
    {
        UINT16 opcode{ 0x60D };
        UserId userId;
        UINT32 grow;
    };
    #pragma pack(pop)
}
