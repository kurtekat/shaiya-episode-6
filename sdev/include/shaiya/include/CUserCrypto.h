#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CUserCrypto
    {
        PAD(564);
        // 0x234
    };
    #pragma pack(pop)

    static_assert(sizeof(CUserCrypto) == 0x234);
}
