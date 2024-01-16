#pragma once
#include <sdev/include/shaiya/common.h>

// CConnection::PacketUserConnect

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentDisconnectIncoming
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentDisconnectOutgoing
    {
        UINT16 opcode{ 0x302 };
        UserId userId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentLogoutIncoming
    {
        UINT16 opcode{ 0x304 };
        UserId userId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentAdminAuthStatusIncoming
    {
        UINT16 opcode{ 0x305 };
        UINT16 authStatus;
        Username username;
    };
    #pragma pack(pop)
}
