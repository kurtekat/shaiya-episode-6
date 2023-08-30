#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemRemakeResult : UINT8
    {
        Success,
        Failure,
        NotAllowed
    };

    struct ItemRemakeIncoming
    {
        UINT16 opcode{ 0x807 };
        UINT8 bag1;
        UINT8 bag2;
        UINT8 bag3;
        UINT8 slot1;
        UINT8 slot2;
        UINT8 slot3;
        ULONG npcId;
    };

    struct ItemRemakeOutgoing
    {
        UINT16 opcode{ 0x807 };
        ItemRemakeResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };
    #pragma pack(pop)
}
