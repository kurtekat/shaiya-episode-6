#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ReloadPointIncoming
    {
        UINT16 opcode{ 0xE06 };
        UserId userId;
    };

    struct ReloadPointOutgoing
    {
        UINT16 opcode{ 0xE06 };
        UserId userId;
        UINT32 points;
    };
    #pragma pack(pop)
}
