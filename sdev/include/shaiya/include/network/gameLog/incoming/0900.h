#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    enum struct GameLogChatType : UINT8
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
    struct GameLogChatIncoming
    {
        UINT16 opcode{ 0x901 };
        ULONG userId;
        ULONG charId;
        UINT16 mapId;
        GameLogChatType chatType;
        UINT8 messageLength;
        CharArray<128> message;

        GameLogChatIncoming() = default;

        GameLogChatIncoming(ULONG userId, ULONG charId, UINT16 mapId, GameLogChatType chatType, const char* message)
            : userId(userId), charId(charId), mapId(mapId), chatType(chatType), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 14;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameLogChatToIncoming
    {
        UINT16 opcode{ 0x902 };
        ULONG userId;
        ULONG charId;
        UINT16 mapId;
        GameLogChatType chatType;
        CharName targetName;
        UINT8 messageLength;
        CharArray<128> message;

        GameLogChatToIncoming() = default;

        GameLogChatToIncoming(ULONG userId, ULONG charId, UINT16 mapId, const char* targetName, const char* message)
            : userId(userId), charId(charId), mapId(mapId), chatType(GameLogChatType::To), targetName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->targetName.data(), this->targetName.size(), targetName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 35;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
