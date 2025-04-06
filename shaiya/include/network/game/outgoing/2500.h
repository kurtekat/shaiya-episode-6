#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
     #pragma pack(push, 1)
    // TP_PVPG_REQ
    struct GamePvPGuildRequestOutgoing
    {
        uint16_t opcode{ 0x2501 };
        uint32_t senderId;
        uint32_t targetId;
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
    // TP_PVPG_ANS
    struct GamePvPGuildAnswerOutgoing
    {
        uint16_t opcode{ 0x2502 };
        GamePvPGuildAnswerResult result;
        uint32_t charId;
    };
    #pragma pack(pop)
}
