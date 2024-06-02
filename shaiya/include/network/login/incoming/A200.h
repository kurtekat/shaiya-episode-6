#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginVersionCheckIncoming
    {
        UINT16 opcode{ 0xA202 };
        UINT8 serverId;
        UINT32 clientVersion;

        LoginVersionCheckIncoming() = default;

        LoginVersionCheckIncoming(UINT8 serverId, UINT32 clientVersion)
            : serverId(serverId), clientVersion(clientVersion)
        {
        }
    };
    #pragma pack(pop)
}
