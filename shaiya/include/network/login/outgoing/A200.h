#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginVersionCheckOutgoing
    {
        UINT16 opcode{ 0xA202 };
        UINT8 serverId;
        UINT32 serverVersion;

        LoginVersionCheckOutgoing() = default;

        LoginVersionCheckOutgoing(UINT8 serverId, UINT32 serverVersion)
            : serverId(serverId), serverVersion(serverVersion)
        {
        }
    };
    #pragma pack(pop)
}
