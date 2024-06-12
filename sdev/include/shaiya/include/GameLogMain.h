#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameLogMain
    {
        ULONG userId;
        CharArray<32> username;
        ULONG charId;
        CharArray<21> charName;
        UINT16 level;
        UINT32 exp;
        UINT16 mapId;
        float x;
        float y;
        float z;
        ULONG actionTime;
    };
    #pragma pack(pop)
}
