#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_CHAT_NORMAL
    struct GameAdminChatNormalIncoming
    {
        uint16_t opcode{ 0xF101 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_CHAT_SENDTO
    struct GameAdminChatSendToIncoming
    {
        uint16_t opcode{ 0xF102 };
        String<21> senderName;
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminChatTradeIncoming
    {
        uint16_t opcode{ 0xF103 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminChatGuildIncoming
    {
        uint16_t opcode{ 0xF104 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_CHAT_SENDPARTY
    struct GameAdminChatPartyIncoming
    {
        uint16_t opcode{ 0xF105 };
        // w/ null-terminator
        uint8_t messageLength;
        String<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameAdminNotifyIncoming
    {
        uint16_t opcode{ 0xF106 };
        // w/ null-terminator
        uint16_t messageLength;
        String<2000> message;
    };
    #pragma pack(pop)
}
