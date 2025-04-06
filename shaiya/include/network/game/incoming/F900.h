#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdMoveCharIncoming
    {
        uint16_t opcode{ 0xF904 };
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminCmdNoticeToIncoming
    {
        uint16_t opcode{ 0xF908 };
        CharName targetName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminCmdNoticeIncoming
    {
        uint16_t opcode{ 0xF90B };
        uint16_t unknown;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)
}
