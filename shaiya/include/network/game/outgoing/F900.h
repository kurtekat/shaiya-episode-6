#pragma once
#include <string>
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketAdminCmdD

namespace shaiya
{
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
            this->messageLength = std::strlen(message) + 1;

            auto result = StringCbCopyA(this->message.data(), this->message.size(), message);
            if (result == STRSAFE_E_INSUFFICIENT_BUFFER)
                this->messageLength = this->message.size();
        }

        AdminCmdNoticeToOutgoing(const std::string& message)
            : messageLength(0), message{}
        {
            this->messageLength = message.length() + 1;

            auto result = StringCbCopyA(this->message.data(), this->message.size(), message.data());
            if (result == STRSAFE_E_INSUFFICIENT_BUFFER)
                this->messageLength = this->message.size();
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
            this->messageLength = std::strlen(message) + 1;

            auto result = StringCbCopyA(this->message.data(), this->message.size(), message);
            if (result == STRSAFE_E_INSUFFICIENT_BUFFER)
                this->messageLength = this->message.size();
        }

        AdminCmdNoticeAllOutgoing(const std::string& message)
            : messageLength(0), message{}
        {
            this->messageLength = message.length() + 1;

            auto result = StringCbCopyA(this->message.data(), this->message.size(), message.data());
            if (result == STRSAFE_E_INSUFFICIENT_BUFFER)
                this->messageLength = this->message.size();
        }

        constexpr int size_without_message() { return 3; }
        constexpr int length() { return size_without_message() + this->messageLength; }
    };
    #pragma pack(pop)
}
