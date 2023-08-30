#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBItemCraftName
    {
        UINT16 opcode; // 0x0717
        ULONG userUid;
        UINT8 bag;
        UINT8 slot;
        char craftName[21];
    };
    #pragma pack(pop)
}
