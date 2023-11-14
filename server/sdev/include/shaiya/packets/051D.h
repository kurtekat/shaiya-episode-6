#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserShapeTypeOutgoing
    {
        UINT16 opcode{ 0x51D };
        ULONG charId;
        ShapeType shapeType;
        #ifdef SHAIYA_EP6_4_PT
        UINT32 vehicleType;
        UINT32 vehicleTypeId;
        #endif
    };
    #pragma pack(pop)
}
