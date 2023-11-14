#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveExpIncoming
    {
        UINT16 opcode{ 0x602 };
        UserId userId;
        UINT32 exp;
    };
    #pragma pack(pop)
}
