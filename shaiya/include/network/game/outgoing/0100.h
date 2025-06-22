#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_CHAR_LIST
    template<class CharacterListT>
    struct GameCharListOutgoing
    {
        uint16_t opcode{ 0x101 };
        uint8_t slot;
        CharacterListT character;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameUserEnterWorldOutgoing
    {
        uint16_t opcode{ 0x104 };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameUserLeaveWorldOutgoing
    {
        uint16_t opcode{ 0x107 };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHAR_COUNTRY
    struct GameCharCountryOutgoing
    {
        uint16_t opcode{ 0x109 };
        Country country;
        Grow maxGrow;
    };
    #pragma pack(pop)

    enum struct GameCharRenameResult : uint8_t
    {
        Success = 1,
        Failure
    };

    #pragma pack(push, 1)
    // TP_CHAR_RENAME
    struct GameCharRenameOutgoing
    {
        uint16_t opcode{ 0x10E };
        GameCharRenameResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_CHARACTER_SERVERTIME
    struct GameCharServerTimeOutgoing
    {
        uint16_t opcode{ 0x114 };
        time32_t time;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // time = localtime + (seconds(hours) + seconds(minutes))
    struct GameCharServerTimeOffsetOutgoing
    {
        uint16_t opcode{ 0x115 };
        time32_t time;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameWeaponStepOutgoing
    {
        uint16_t opcode{ 0x116 };
        Array<uint16_t, 21> weaponStep;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameGuildCharNameOutgoing
    {
        uint16_t opcode{ 0x117 };
        uint32_t objectId;
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharNameAvailableOutgoing
    {
        uint16_t opcode{ 0x119 };
        bool available;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameSystemMessageOutgoing
    {
        uint16_t opcode{ 0x122 };
        bool32_t isNotification;
        uint32_t messageNumber;
    };
    #pragma pack(pop)
}
