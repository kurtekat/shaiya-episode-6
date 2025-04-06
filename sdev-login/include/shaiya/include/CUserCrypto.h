#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CUserCrypto
    {
        PAD(644);
        // 0x284
    };
    #pragma pack(pop)

    static_assert(sizeof(CUserCrypto) == 0x284);
}
