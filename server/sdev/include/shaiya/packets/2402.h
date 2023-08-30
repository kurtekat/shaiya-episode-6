#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct BattleRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    struct BattleRequestResultIncoming
    {
        UINT16 opcode{ 0x2402 };
        BattleRequestResult result;
    };

    struct BattleRequestResultOutgoing
    {
        UINT16 opcode{ 0x2402 };
        BattleRequestResult result;
        CharId targetId;
    };
    #pragma pack(pop)
}
