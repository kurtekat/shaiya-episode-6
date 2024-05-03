#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginVersionCheckIncoming
    {
        UINT16 opcode{ 0xA202 };
        UINT8 serverId;
        UINT32 serverVersion;
    };
    #pragma pack(pop)
}
