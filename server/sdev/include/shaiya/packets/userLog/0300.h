#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SessionDisconnectIncoming
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
        UINT64 sessionId;
        UINT8 closeType;
        UINT32 closeErr;
    };

    struct SessionDisconnectOutgoing
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
    };
    #pragma pack(pop)
}
