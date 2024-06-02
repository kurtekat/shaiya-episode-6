#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameLogMain
    {
        ULONG userId;
        Username username;
        ULONG charId;
        CharName charName;
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
