#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct PresentReceivedOutgoing
    {
        UINT16 opcode{ 0x2604 };
        CharName senderName;
        ProductCode productCode;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)
}
