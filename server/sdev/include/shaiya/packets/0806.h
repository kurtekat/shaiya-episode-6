#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemComposeResult : UINT8
    {
        Success,
        Failure
    };

    struct ItemComposeOutgoing
    {
        UINT16 opcode{ 0x806 };
        ItemComposeResult result;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;
    };
    #pragma pack(pop)
}
