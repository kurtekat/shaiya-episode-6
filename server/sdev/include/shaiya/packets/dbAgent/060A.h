#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveLevelIncoming
    {
        UINT16 opcode{ 0x60A };
        UserId userId;
        UINT32 level;
    };
    #pragma pack(pop)
}
