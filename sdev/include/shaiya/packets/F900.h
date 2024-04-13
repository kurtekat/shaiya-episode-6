#pragma once
#include <include/shaiya/common.h>

// CUser::PacketAdminCmdD

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdNoticeToIncoming
    {
        UINT16 opcode{ 0xF908 };
        CharName targetName;
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminCmdNoticeToOutgoing
    {
        UINT16 opcode{ 0xF908 };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
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
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminCmdNoticeAllOutgoing
    {
        UINT16 opcode{ 0xF90B };
        // w/ null-terminator
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)
}
