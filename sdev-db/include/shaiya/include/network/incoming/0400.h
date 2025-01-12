#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketUserChar

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentCharNameChangeIncoming
    {
        UINT16 opcode{ 0x409 };
        ULONG userId;
        ULONG charId;
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharDeleteIncoming
    {
        UINT16 opcode{ 0x40A };
        ULONG userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharRestoreIncoming
    {
        UINT16 opcode{ 0x40B };
        ULONG userId;
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct DBAgentCharNameAvailableIncoming
    {
        UINT16 opcode{ 0x40D };
        ULONG userId;
        CharArray<19> name;
    };
    #pragma pack(pop)
}
