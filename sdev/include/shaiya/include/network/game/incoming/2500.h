#pragma once
#include <shaiya/include/common.h>

// CUser::PacketPvPGuild

namespace shaiya
{
    #pragma pack(push, 1)
    struct PvPGuildRequestIncoming
    {
        UINT16 opcode{ 0x2501 };
        ULONG senderId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPGuildRequestResultIncoming
    {
        UINT16 opcode{ 0x2502 };
        enum struct Result : UINT8 {
            Rejected,
            Accepted,
            CannotRequest,
            DidNotRespond
        } result;
    };
    #pragma pack(pop)
}
