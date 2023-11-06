#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct PortalUseOutgoing
    {
        UINT16 opcode{ 0x20B };
        UINT8 portalId;
        UINT16 destMapId;
        float destX;
        float destY;
        float destZ;
    };
    #pragma pack(pop)
}
