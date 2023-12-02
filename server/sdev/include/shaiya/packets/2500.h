#pragma once
#include <include/shaiya/common.h>

// CUser::PacketPvPGuild

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct PvPGuildRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    struct PvPGuildRequestIncoming
    {
        UINT16 opcode{ 0x2501 };
        CharId senderId;
    };

    struct PvPGuildRequestOutgoing
    {
        UINT16 opcode{ 0x2501 };
        CharId senderId;
        CharId targetId;
    };

    struct PvPGuildRequestResultIncoming
    {
        UINT16 opcode{ 0x2502 };
        PvPGuildRequestResult result;
    };

    struct PvPGuildRequestResultOutgoing
    {
        UINT16 opcode{ 0x2502 };
        PvPGuildRequestResult result;
        CharId targetId;
    };
    #pragma pack(pop)
}
