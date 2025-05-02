#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_DB_CHAR_LIST
    template<class DBCharacterListT>
    struct DBAgentCharListOutgoing
    {
        uint16_t opcode{ 0x403 };
        uint32_t billingId;
        bool withCountry;
        uint8_t characterCount;
        Array<DBCharacterListT, 5> characterList;

        constexpr static int baseLength = 8;
    };
    #pragma pack(pop)

    enum struct DBAgentCharCreateResult : uint8_t
    {
        Success,
        Failure
    };

    #pragma pack(push, 1)
    // TP_DB_CHAR_CREATE
    struct DBAgentCharCreateOutgoing
    {
        uint16_t opcode{ 0x404 };
        uint32_t billingId;
        DBAgentCharCreateResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_CHAR_RENAME
    struct DBAgentCharRenameOutgoing
    {
        uint16_t opcode{ 0x409 };
        uint32_t billingId;
        uint8_t result;
        uint32_t charId;
        String<21> oldCharName;
        String<21> newCharName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_DB_CHAR_DELETE
    struct DBAgentCharDeleteOutgoing
    {
        uint16_t opcode{ 0x40A };
        uint32_t billingId;
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharRestoreOutgoing
    {
        uint16_t opcode{ 0x40B };
        uint32_t billingId;
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct DBAgentCharNameAvailableOutgoing
    {
        uint16_t opcode{ 0x40D };
        uint32_t billingId;
        bool available;
    };
    #pragma pack(pop)
}
