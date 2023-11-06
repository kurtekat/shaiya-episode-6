#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemDropType : UINT8
    {
        Character = 1,
        Monster
    };

    struct ItemDropIncoming
    {
        UINT16 opcode{ 0x401 };
        ULONG id;
        ItemDropType dropType;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)
}
