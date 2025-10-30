#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "SaveType.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct ConcernMarket
    {
        CRITICAL_SECTION cs;  //0x00
        SaveType saveType;    //0x18
        uint8_t count;        //0x1C
        PAD(3);
        // 0x20
        Array<uint32_t, 10> marketIds;
        // 0x48
    };
    #pragma pack(pop)

    static_assert(sizeof(ConcernMarket) == 0x48);
}
