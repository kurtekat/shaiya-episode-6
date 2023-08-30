#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct RuneCombineResult : UINT8
    {
        Success,
        NotImplemented,
        Failure
    };

    struct RuneCombineRequest
    {
        UINT16 opcode; // 0x80D
        UINT8 runeBag;
        UINT8 runeSlot;
        UINT8 vialBag;
        UINT8 vialSlot;
        ULONG npcId;
    };

    struct RuneCombineResponse
    {
        UINT16 opcode; // 0x80D
        RuneCombineResult result;
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
