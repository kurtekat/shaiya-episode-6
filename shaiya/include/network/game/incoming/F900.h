#pragma once
#include <array>
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/user/CharName.h>

// CUser::PacketAdminCmdD

namespace shaiya
{
    using ChatMessage = std::array<char, 128>;

    #pragma pack(push, 1)
    struct AdminCmdNoticeToIncoming
    {
        UINT16 opcode{ 0xF908 };
        CharName targetName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        AdminCmdNoticeToIncoming() = default;

        AdminCmdNoticeToIncoming(const char* targetName, const char* message)
            : targetName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->targetName.data(), this->targetName.size(), targetName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 24; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminCmdNoticeAllIncoming
    {
        UINT16 opcode{ 0xF90B };
        UINT16 unknown;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        AdminCmdNoticeAllIncoming() = default;

        AdminCmdNoticeAllIncoming(const char* message)
            : unknown(0), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 5; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)
}
