#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 180
    // TP_GAMELOG_ADMIN_CMDTA
    struct GameLogAdminCmdAIncoming
    {
        uint16_t opcode{ 0xC01 };
        uint32_t billingId;
        Username username;
        uint32_t charId;
        CharName charName;
        uint16_t mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        CharArray<32> cmdName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 180
    // TP_GAMELOG_ADMIN_CMDTB
    struct GameLogAdminCmdBIncoming
    {
        uint16_t opcode{ 0xC02 };
        uint32_t billingId;
        Username username;
        uint32_t charId;
        CharName charName;
        uint16_t mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        CharArray<32> cmdName;
        CharName targetName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 180
    // TP_GAMELOG_ADMIN_CMDTC
    struct GameLogAdminCmdCIncoming
    {
        uint16_t opcode{ 0xC03 };
        uint32_t billingId;
        Username username;
        uint32_t charId;
        CharName charName;
        uint16_t mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        CharArray<32> cmdName;
        CharName targetName;
        CharArray<256> cmdInfo;
    };
    #pragma pack(pop)
}
