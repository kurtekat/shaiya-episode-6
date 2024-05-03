#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/AuthStatus.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // ActionType 180
    struct GameLogAdminCmd1Incoming
    {
        UINT16 opcode{ 0xC01 };
        ULONG userId;
        CharArray<32> username;
        ULONG charId;
        CharArray<21> charName;
        UINT16 mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        CharArray<32> desc;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 180
    struct GameLogAdminCmd2Incoming
    {
        UINT16 opcode{ 0xC02 };
        ULONG userId;
        CharArray<32> username;
        ULONG charId;
        CharArray<21> charName;
        UINT16 mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        CharArray<32> desc;
        CharArray<21> targetName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // ActionType 180
    struct GameLogAdminCmd3Incoming
    {
        UINT16 opcode{ 0xC03 };
        ULONG userId;
        CharArray<32> username;
        ULONG charId;
        CharArray<21> charName;
        UINT16 mapId;
        float x;
        float y;
        float z;
        AuthStatus authStatus;
        CharArray<32> desc;
        CharArray<21> targetName;
        // e.g. "name=%s"
        CharArray<256> text;
    };
    #pragma pack(pop)
}
