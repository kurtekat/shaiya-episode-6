#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBQuickSlot
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 srcBag;
        UINT16 srcSlot;
    };

    struct SaveQuickSlot
    {
        UINT16 opcode{ 0x609 };
        UserId userId;
        UINT8 quickSlotCount;
        // size = quickSlotCount
        Array<DBQuickSlot, 128> quickSlot;
    };
    #pragma pack(pop)
}
