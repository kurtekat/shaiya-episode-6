#pragma once
#include <shaiya/common.h>

namespace shaiya
{
#pragma pack(push, 1)
    struct UpdateItemStatePacket {
        WORD opcode; // 0x0206
        BYTE bag;
        BYTE slot;
        BYTE type;
        BYTE typeId;
        BYTE count;
    };
#pragma pack(pop)
}
