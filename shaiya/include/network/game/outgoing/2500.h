#pragma once
#include <shaiya/include/common.h>

// CUser::PacketPvPGuild

namespace shaiya
{
    enum struct PvPGuildRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    #pragma pack(push, 1)
    struct PvPGuildRequestIncoming
    {
        UINT16 opcode{ 0x2501 };
        ULONG senderId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPGuildRequestOutgoing
    {
        UINT16 opcode{ 0x2501 };
        ULONG senderId;
        ULONG targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPGuildRequestResultIncoming
    {
        UINT16 opcode{ 0x2502 };
        PvPGuildRequestResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPGuildRequestResultOutgoing
    {
        UINT16 opcode{ 0x2502 };
        PvPGuildRequestResult result;
        ULONG targetId;
    };
    #pragma pack(pop)
}
