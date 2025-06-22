#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdDNoticeToOutgoing
    {
        uint16_t opcode{ 0xF908 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 3;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ADMIN_CMDS_NOTICE
    struct GameAdminCmdDNoticeOutgoing
    {
        uint16_t opcode{ 0xF90B };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 3;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
