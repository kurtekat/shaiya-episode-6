#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct GameLogChatType : uint8_t
    {
        Normal = 1,
        To,
        Guild,
        Party,
        Trade = 5,
        All = 5,
        Shout,
        Zone
    };

    #pragma pack(push, 1)
    // TP_GAMELOG_CHAT_A
    struct GameLogChatAIncoming
    {
        uint16_t opcode{ 0x901 };
        uint32_t billingId;
        uint32_t charId;
        uint16_t mapId;
        GameLogChatType chatType;
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 14;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_GAMELOG_CHAT_B
    struct GameLogChatBIncoming
    {
        uint16_t opcode{ 0x902 };
        uint32_t billingId;
        uint32_t charId;
        uint16_t mapId;
        GameLogChatType chatType;
        String<21> targetName;
        uint8_t messageLength;
        String<128> message;

        constexpr static int baseLength = 35;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
