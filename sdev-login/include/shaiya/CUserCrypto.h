#pragma once
#include <shaiya/include/common.h>
#include "SAes.h"
#include "SRsaEnc.h"

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CUserCrypto
    {
        CUser* user;                    //0x00
        Array<uint8_t, 16> sessionKey;  //0x04
        bool initKey;                   //0x14
        bool initPublicKey;             //0x15
        PAD(2);
        SRsaEnc rsaEnc;                 //0x18
        Array<uint8_t, 32> aesKey;      //0x34
        SAes aesEnc;                    //0x54
        SAes aesDec;                    //0x16C
        // 0x284
    };
    #pragma pack(pop)

    static_assert(sizeof(CUserCrypto) == 0x284);
}
