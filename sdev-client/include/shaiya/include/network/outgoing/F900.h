#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdNoticeToOutgoing
    {
        UINT16 opcode{ 0xF908 };
        CharName targetName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminCmdNoticeToOutgoing() = default;

        AdminCmdNoticeToOutgoing(const char* targetName, const char* message)
            : targetName{}, messageLength(0), message{}
        {
            StringCbCopyA(this->targetName.data(), this->targetName.size(), targetName);
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 24;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminCmdNoticeAllOutgoing
    {
        UINT16 opcode{ 0xF90B };
        UINT16 unknown;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;

        AdminCmdNoticeAllOutgoing() = default;

        AdminCmdNoticeAllOutgoing(const char* message)
            : unknown(0), messageLength(0), message{}
        {
            StringCbCopyA(this->message.data(), this->message.size(), message);
            this->messageLength = static_cast<UINT8>(std::strlen(this->message.data()) + 1);
        }

        constexpr static int baseLength = 5;
        constexpr int length() const { return baseLength + this->messageLength; }
    };
    #pragma pack(pop)
}
