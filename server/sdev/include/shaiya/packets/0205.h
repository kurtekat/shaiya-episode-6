#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ZonePickItemIncoming
    {
        UINT16 opcode{ 0x205 };
        ULONG id;
    };

    struct ItemAcquiredOutgoing
    {
        UINT16 opcode{ 0x205 };
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        // or '\0'
        CraftName craftName;
    };
    #pragma pack(pop)
}
