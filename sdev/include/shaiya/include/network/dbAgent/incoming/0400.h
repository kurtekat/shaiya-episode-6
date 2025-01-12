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

        DBAgentCharNameChangeIncoming() = default;

        DBAgentCharNameChangeIncoming(ULONG userId, ULONG charId, const char* charName)
            : userId(userId), charId(charId), charName{}
        {
            StringCbCopyA(this->charName.data(), this->charName.size(), charName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharDeleteIncoming
    {
        UINT16 opcode{ 0x40A };
        ULONG userId;
        ULONG charId;

        DBAgentCharDeleteIncoming() = default;

        DBAgentCharDeleteIncoming(ULONG userId, ULONG charId)
            : userId(userId), charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharRestoreIncoming
    {
        UINT16 opcode{ 0x40B };
        ULONG userId;
        ULONG charId;

        DBAgentCharRestoreIncoming() = default;

        DBAgentCharRestoreIncoming(ULONG userId, ULONG charId)
            : userId(userId), charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct DBAgentCharNameAvailableIncoming
    {
        UINT16 opcode{ 0x40D };
        ULONG userId;
        CharArray<19> name;

        DBAgentCharNameAvailableIncoming() = default;

        DBAgentCharNameAvailableIncoming(ULONG userId, const char* name)
            : userId(userId), name{}
        {
            StringCbCopyA(this->name.data(), this->name.size(), name);
        }

        constexpr static int baseLength = 6;
    };
    #pragma pack(pop)
}
