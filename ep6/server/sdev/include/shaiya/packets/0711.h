#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct WarehouseItem
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        // or CloakBadge
        UINT8 gems[6];
        UINT8 count;
        #ifdef SHAIYA_EP6
        ULONG fromDate;
        ULONG toDate;
        #endif
        char craftName[21];
    };

    struct CharacterWarehouse
    {
        UINT16 opcode; // 0x711
        UINT32 money;
        UINT8 itemCount;
        #ifdef SHAIYA_EP6
        WarehouseItem items[40];
        #else
        WarehouseItem items[50]
        #endif
    };
    #pragma pack(pop)
}
