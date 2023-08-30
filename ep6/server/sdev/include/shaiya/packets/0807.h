#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemRemakeResult : UINT8
    {
        Success,
        Failure,
        NotAllowed
    };

    struct ItemRemakeRequest
    {
        UINT16 opcode; // 0x807
        UINT8 bag1;
        UINT8 bag2;
        UINT8 bag3;
        UINT8 slot1;
        UINT8 slot2;
        UINT8 slot3;
        ULONG npcId;
    };

    struct ItemRemakeResponse
    {
        UINT16 opcode; // 0x807
        ItemRemakeResult result;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        UINT8 gems[6];
        UINT8 count;
        char craftName[21];
    };
    #pragma pack(pop)
}
