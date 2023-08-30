#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserMoveIncoming
    {
        UINT16 opcode{ 0x501 };
        // CUser->144D
        UINT8 unknown;
        UINT16 direction;
        float x;
        float y;
        float z;
    };

    struct UserMoveOutgoing
    {
        UINT16 opcode{ 0x501 };
        ULONG charId;
        // CUser->144D
        UINT8 unknown;
        UINT16 direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)
}
