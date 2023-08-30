#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExchangeItemAdd
    {
        UINT16 opcode{ 0xA06 };
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 count;
        UINT8 destSlot;
    };
    #pragma pack(pop)
}
