#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // aes_key_st
    struct AesKey
    {
        Array<int32_t, 60> roundKey;
        int32_t rounds;
        // 0xF4
    };
    #pragma pack(pop)

    static_assert(sizeof(AesKey) == 0xF4);
}
