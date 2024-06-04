#pragma once
#include <array>
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/user/CharName.h>

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

        CharacterCreateIncoming() = default;

        CharacterCreateIncoming(UINT8 slot, Family family, Grow grow, UINT8 hair, UINT8 face, UINT8 size, Job job, Sex sex, const char* charName)
            : slot(slot), family(family), grow(grow), hair(hair), face(face), size(size), job(job), sex(sex), charName{}
        {
            StringCbCopyA(this->charName.data(), this->charName.size(), charName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterDeleteIncoming
    {
        UINT16 opcode{ 0x103 };
        ULONG charId;

        CharacterDeleteIncoming() = default;

        CharacterDeleteIncoming(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterNameChangeIncoming
    {
        UINT16 opcode{ 0x10E };
        ULONG charId;
        CharName charName;

        CharacterNameChangeIncoming() = default;

        CharacterNameChangeIncoming(ULONG charId, const char* charName)
            : charId(charId), charName{}
        {
            StringCbCopyA(this->charName.data(), this->charName.size(), charName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharacterRestoreIncoming
    {
        UINT16 opcode{ 0x10F };
        ULONG charId;

        CharacterRestoreIncoming() = default;

        CharacterRestoreIncoming(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharNameAvailableIncoming
    {
        UINT16 opcode{ 0x119 };
        std::array<char, 19> name;

        CharNameAvailableIncoming() = default;

        CharNameAvailableIncoming(const char* charName)
            : name{}
        {
            StringCbCopyA(this->name.data(), this->name.size(), charName);
        }
    };
    #pragma pack(pop)
}
