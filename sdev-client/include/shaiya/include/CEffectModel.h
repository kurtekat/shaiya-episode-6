#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    // 0057CD30 ctor
    struct CEffectModel
    {
        PAD(16);
        CharArray<16> fileName;  //0x10
        // 0x20
        PAD(20);
        // 0x34
    };
}
