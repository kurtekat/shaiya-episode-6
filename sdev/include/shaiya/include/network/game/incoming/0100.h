#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

// CUser::PacketCharacter

namespace shaiya
{
    #pragma pack(push, 1)
    struct CharCreateIncoming
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
        CharArray<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharDeleteIncoming
    {
        UINT16 opcode{ 0x103 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharChangeIncoming
    {
        UINT16 opcode{ 0x107 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuickSlot010B
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 srcBag;
        UINT16 srcSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharQuickSlotIncoming
    {
        UINT16 opcode{ 0x10B };
        UINT8 quickSlotCount;
        Array<QuickSlot010B, 128> quickSlots;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharExitIncoming
    {
        UINT16 opcode{ 0x10D };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharNameChangeIncoming
    {
        UINT16 opcode{ 0x10E };
        ULONG charId;
        CharArray<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharRestoreIncoming
    {
        UINT16 opcode{ 0x10F };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CharNameAvailableIncoming
    {
        UINT16 opcode{ 0x119 };
        CharArray<19> name;
    };
    #pragma pack(pop)
}
