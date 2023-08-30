#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveStatusUp
    {
        UINT16 opcode{ 0x604 };
        UserId userId;
        UINT16 statPoint;
        UINT16 strength;
        UINT16 dexterity;
        UINT16 recovery;
        UINT16 intelligence;
        UINT16 wisdom;
        UINT16 luck;
    };
    #pragma pack(pop)
}
