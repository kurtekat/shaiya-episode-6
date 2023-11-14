#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SaveItemCraftNameIncoming
    {
        UINT16 opcode{ 0x717 };
        UserId userId;
        UINT8 bag;
        UINT8 slot;
        CraftName craftName;
    };
    #pragma pack(pop)
}
