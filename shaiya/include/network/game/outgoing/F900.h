#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameAdminCmdNoticeToOutgoing
    {
        uint16_t opcode{ 0xF908 };
        // w/ null-terminator
        uint8_t messageLength;
        CharArray<128> message;

        constexpr static int baseLength = 3;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ADMIN_CMDS_NOTICE
    struct GameAdminCmdNoticeOutgoing
    {
        uint16_t opcode{ 0xF90B };
        // w/ null-terminator
        uint8_t messageLength;
        CharArray<128> message;

        constexpr static int baseLength = 3;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
