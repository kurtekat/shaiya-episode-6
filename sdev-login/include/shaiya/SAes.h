#pragma once
#include <shaiya/include/common.h>
#include "AesKey.h"

namespace shaiya
{
    #pragma pack(push, 1)
    // AES-128-CTR
    struct SAes
    {
        AesKey key;                 //0x00
        Array<uint8_t, 16> iv;      //0xF4
        int32_t ivPos;              //0x104
        Array<uint8_t, 16> encCtr;  //0x108
        // 0x118
    };
    #pragma pack(pop)

    static_assert(sizeof(SAes) == 0x118);
}
