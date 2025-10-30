#pragma once
#include <mini-gmp/mini-gmp.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SRsa
    {
        __mpz_struct e[1];    //0x00
        __mpz_struct d[1];    //0x0C
        __mpz_struct n[1];    //0x18
        __mpz_struct p[1];    //0x24
        __mpz_struct q[1];    //0x30
        __mpz_struct ep[1];   //0x3C
        __mpz_struct eq[1];   //0x48
        __mpz_struct piq[1];  //0x54
        __mpz_struct t[1];    //0x60
        __mpz_struct c[1];    //0x6C
        __mpz_struct m[1];    //0x78
        // 0x84
    };
    #pragma pack(pop)

    static_assert(sizeof(SRsa) == 0x84);
}
