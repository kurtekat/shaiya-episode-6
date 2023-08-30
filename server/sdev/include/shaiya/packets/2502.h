#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct GvGRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    struct GvGRequestResultIncoming
    {
        UINT16 opcode{ 0x2502 };
        GvGRequestResult result;
    };

    struct GvGRequestResultOutgoing
    {
        UINT16 opcode{ 0x2502 };
        GvGRequestResult result;
        CharId targetId;
    };
    #pragma pack(pop)
}
