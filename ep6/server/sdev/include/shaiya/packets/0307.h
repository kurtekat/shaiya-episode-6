#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct InspectEquipment
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        // or CloakBadge
        UINT8 gems[6];
        char craftName[21];
    };

    struct InspectRequest
    {
        UINT16 opcode; // 0x307
        ULONG charId;
    };

    struct InspectResponse
    {
        UINT16 opcode; // 0x307
        UINT8 itemCount;
        #ifdef SHAIYA_EP6
        InspectEquipment list[17];
        #else
        InspectEquipment list[12];
        #endif
    };
    #pragma pack(pop)
}
