#pragma once
#include <array>
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketAdminCmdD

namespace shaiya
{
    using ChatMessage = std::array<char, 128>;

    #pragma pack(push, 1)
    struct AdminCmdNoticeToOutgoing
    {
        UINT16 opcode{ 0xF908 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        AdminCmdNoticeToOutgoing() = default;

        AdminCmdNoticeToOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminCmdNoticeAllOutgoing
    {
        UINT16 opcode{ 0xF90B };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;

        AdminCmdNoticeAllOutgoing() = default;

        AdminCmdNoticeAllOutgoing(const char* message)
            : messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)
}
