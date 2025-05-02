#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_DB_CHAR_RENAME
    struct DBAgentCharRenameIncoming
    {
        uint16_t opcode{ 0x409 };
        uint32_t billingId;
        uint32_t charId;
        String<21> charName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_DB_CHAR_DELETE
    struct DBAgentCharDeleteIncoming
    {
        uint16_t opcode{ 0x40A };
        uint32_t billingId;
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentCharRestoreIncoming
    {
        uint16_t opcode{ 0x40B };
        uint32_t billingId;
        uint32_t charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // custom
    struct DBAgentCharNameAvailableIncoming
    {
        uint16_t opcode{ 0x40D };
        uint32_t billingId;
        String<19> name;

        constexpr static int baseLength = 6;
    };
    #pragma pack(pop)
}
