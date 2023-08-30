#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CharNameAvailableRequest
    {
        UINT16 opcode; // 0x119
        char name[19];
    };

    struct CharNameAvailableResponse
    {
        UINT16 opcode; // 0x119
        bool available;
    };
    #pragma pack(pop)
}
