#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/user/AuthStatus.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 180
    struct GameLogAdminCmd1Incoming
    {
        UINT16 opcode{ 0xC01 };
        ULONG userId;
        Username username;
        ULONG charId;
        CharName charName;
        UINT16 mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        std::array<char, 32> desc;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 180
    struct GameLogAdminCmd2Incoming
    {
        UINT16 opcode{ 0xC02 };
        ULONG userId;
        Username username;
        ULONG charId;
        CharName charName;
        UINT16 mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        std::array<char, 32> desc;
        CharName targetName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 180
    struct GameLogAdminCmd3Incoming
    {
        UINT16 opcode{ 0xC03 };
        ULONG userId;
        Username username;
        ULONG charId;
        CharName charName;
        UINT16 mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        std::array<char, 32> desc;
        CharName targetName;
        // e.g. "name=%s"
        std::array<char, 256> text;
    };
    #pragma pack(pop)
}
