#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/network/game/QuickUnit.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameCharCreateIncoming
    {
        uint16_t opcode{ 0x102 };
        uint8_t slot;
        Family family;
        Grow grow;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Job job;
        Sex sex;
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharDeleteIncoming
    {
        uint16_t opcode{ 0x103 };
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharEnterWorldIncoming
    {
        uint16_t opcode{ 0x104 };
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharLeaveWorldIncoming
    {
        uint16_t opcode{ 0x107 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharQuickSlotIncoming
    {
        uint16_t opcode{ 0x10B };
        uint8_t quickSlotCount;
        Array<QuickUnit, 128> quickSlotList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_CHAR_RENAME
    struct GameCharRenameIncoming
    {
        uint16_t opcode{ 0x10E };
        uint32_t charId;
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharRestoreIncoming
    {
        uint16_t opcode{ 0x10F };
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharNameAvailableIncoming
    {
        uint16_t opcode{ 0x119 };
        String<19> name;
    };
    #pragma pack(pop)
}
