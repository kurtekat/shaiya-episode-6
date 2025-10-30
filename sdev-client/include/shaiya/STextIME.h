#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // 005D0A70 ctor
    struct STextIME
    {
        void* vftable;  //0x00
        PAD(1044);
        HWND hwnd;      //0x418
        PAD(32);
        // 0x43C
    };
    #pragma pack(pop)

    static_assert(sizeof(STextIME) == 0x43C);
}
