#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RequiredItemsPacket
    {
        WORD opcode; // 0x0831
        // 10000
        DWORD successRate;
        BYTE type[24];
        BYTE rewardType;
        BYTE typeId[24];
        BYTE rewardTypeId;
        BYTE count[24];
        BYTE rewardCount;
    };
    #pragma pack(pop)
}
