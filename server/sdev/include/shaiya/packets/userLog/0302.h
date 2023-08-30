#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // values are passed to [dbo].[usp_Try_GameLogout_R]
    struct DisconnectIncoming
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
        UINT64 sessionId;
        UINT8 closeType;
        UINT32 closeErr;
    };

    struct DisconnectOutgoing
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
    };
    #pragma pack(pop)
}
