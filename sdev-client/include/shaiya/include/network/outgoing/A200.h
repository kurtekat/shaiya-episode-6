#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginVersionCheckOutgoing
    {
        UINT16 opcode{ 0xA202 };
        UINT8 serverId;
        UINT32 clientVersion;

        LoginVersionCheckOutgoing() = default;

        LoginVersionCheckOutgoing(UINT8 serverId, UINT32 clientVersion)
            : serverId(serverId), clientVersion(clientVersion)
        {
        }
    };
    #pragma pack(pop)
}
