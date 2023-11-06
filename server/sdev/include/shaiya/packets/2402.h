#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct PvPRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    struct PvPRequestResultIncoming
    {
        UINT16 opcode{ 0x2402 };
        PvPRequestResult result;
    };

    struct PvPRequestResultOutgoing
    {
        UINT16 opcode{ 0x2402 };
        PvPRequestResult result;
        CharId targetId;
    };
    #pragma pack(pop)
}
