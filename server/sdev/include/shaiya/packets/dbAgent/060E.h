#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveSkillPoint
    {
        UINT16 opcode{ 0x60E };
        UserId userId;
        UINT32 skillPoint;
    };
    #pragma pack(pop)
}
