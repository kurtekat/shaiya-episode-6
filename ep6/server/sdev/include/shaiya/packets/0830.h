#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ListItemsPacket
    {
        WORD opcode; // 0x0830
        BYTE type[10];
        BYTE typeId[10];
        DWORD goldPerPercentage;
    };
    #pragma pack(pop)
}
