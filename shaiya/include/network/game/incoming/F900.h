#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdDMoveCharIncoming
    {
        uint16_t opcode{ 0xF904 };
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminCmdDNoticeToIncoming
    {
        uint16_t opcode{ 0xF908 };
        String<21> targetName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminCmdDNoticeIncoming
    {
        uint16_t opcode{ 0xF90B };
        uint16_t unknown;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)
}
