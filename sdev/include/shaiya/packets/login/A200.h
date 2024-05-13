#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct VersionCheckIncoming
    {
        UINT16 opcode{ 0xA202 };
        UINT8 serverId;
        UINT32 clientVersion;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VersionCheckOutgoing
    {
        UINT16 opcode{ 0xA202 };
        UINT8 serverId;
        UINT32 serverVersion;
    };
    #pragma pack(pop)
}
