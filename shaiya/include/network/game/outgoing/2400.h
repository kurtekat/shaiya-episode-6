#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/item/CraftName.h>
#include <shaiya/include/item/Gems.h>

// CUser::PacketPvP

namespace shaiya
{
    #pragma pack(push, 1)
    struct PvPExchangeItemOutgoing
    {
        UINT16 opcode{ 0x240D };
        UINT8 destSlot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
#ifdef SHAIYA_EP6_4_PT
        ULONG fromDate;
        ULONG toDate;
#endif
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)
}
