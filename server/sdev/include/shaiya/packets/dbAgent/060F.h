#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveStatPointIncoming
    {
        UINT16 opcode{ 0x60F };
        UserId userId;
        UINT32 statPoint;
    };
    #pragma pack(pop)
}
