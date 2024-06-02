#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

// CUser::PacketCharacter

namespace shaiya
{
    #pragma pack(push, 1)
    struct CharacterCreateIncoming
    {
        UINT16 opcode{ 0x102 };
        UINT8 slot;
        Family family;
        Grow grow;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterDeleteIncoming
    {
        UINT16 opcode{ 0x103 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterNameChangeIncoming
    {
        UINT16 opcode{ 0x10E };
        ULONG charId;
        CharName charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterRestoreIncoming
    {
        UINT16 opcode{ 0x10F };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharNameAvailableIncoming
    {
        UINT16 opcode{ 0x119 };
        std::array<char, 19> name;
    };
    #pragma pack(pop)
}
