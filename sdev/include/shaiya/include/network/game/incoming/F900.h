#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketAdminCmdD

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminCmdNoticeToIncoming
    {
        UINT16 opcode{ 0xF908 };
        CharArray<21> targetName;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AdminCmdNoticeAllIncoming
    {
        UINT16 opcode{ 0xF90B };
        UINT16 unknown;
        // w/ null-terminator
        UINT8 messageLength;
        CharArray<128> message;
    };
    #pragma pack(pop)
}
