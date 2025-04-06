#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GamePvPGuildRequestIncoming
    {
        uint16_t opcode{ 0x2501 };
        uint32_t senderId;
    };
    #pragma pack(pop)

    enum struct GamePvPGuildAnswerResult : uint8_t
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    #pragma pack(push, 1)
    // TPC_PVPG_ANS
    struct GamePvPGuildAnswerIncoming
    {
        uint16_t opcode{ 0x2502 };
        GamePvPGuildAnswerResult result;
    };
    #pragma pack(pop)
}
