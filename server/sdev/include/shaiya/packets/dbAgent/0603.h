#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveMoneyIncoming
    {
        UINT16 opcode{ 0x603 };
        UserId userId;
        UINT32 money;
    };
    #pragma pack(pop)
}
