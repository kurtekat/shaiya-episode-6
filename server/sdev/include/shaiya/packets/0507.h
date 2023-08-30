#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SendEquipment
    {
        UINT16 opcode{ 0x507 };
        ULONG charId;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
    };
    #pragma pack(pop)
}
