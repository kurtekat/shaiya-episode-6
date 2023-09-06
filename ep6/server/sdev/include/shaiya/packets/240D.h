#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BattleExchangeUserItem
    {
        UINT16 opcode; // 0x240D
        UINT8 destSlot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        // or CloakBadge
        UINT8 gems[6];
        #ifdef SHAIYA_EP6
        ULONG fromDate;
        ULONG toDate;
        #endif
        char craftName[21];
    };
    #pragma pack(pop)
}
