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
    struct PvPGuildRequestOutgoing
    {
        UINT16 opcode{ 0x2501 };
        ULONG senderId;
        ULONG targetId;

        PvPGuildRequestOutgoing() = default;

        PvPGuildRequestOutgoing(ULONG senderId, ULONG targetId)
            : senderId(senderId), targetId(targetId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPGuildRequestResultOutgoing
    {
        UINT16 opcode{ 0x2502 };
        PvPGuildRequestResult result;
        ULONG targetId;

        PvPGuildRequestResultOutgoing() = default;

        PvPGuildRequestResultOutgoing(PvPGuildRequestResult result, ULONG targetId)
            : result(result), targetId(targetId)
        {
        }
    };
    #pragma pack(pop)
}
