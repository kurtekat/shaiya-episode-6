#pragma once
#include <mini-gmp/mini-gmp.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct SRsa;

    #pragma pack(push, 1)
    struct SRsaEnc
    {
        SRsa* rsa;          //0x00
        __mpz_struct c[1];  //0x04
        __mpz_struct m[1];  //0x10
        // 0x1C
    };
    #pragma pack(pop)

    static_assert(sizeof(SRsaEnc) == 0x1C);
}
