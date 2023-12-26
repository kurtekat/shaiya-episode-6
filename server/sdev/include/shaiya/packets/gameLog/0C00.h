#pragma once
#include <include/shaiya/common.h>

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
        Array<char, 32> desc;
    };

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
        Array<char, 32> desc;
        CharName targetName;
    };

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
        Array<char, 32> desc;
        CharName targetName;
        // e.g. "name=%s"
        Array<char, 256> text;
    };
    #pragma pack(pop)
}
