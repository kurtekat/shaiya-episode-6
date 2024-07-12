#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CUserCrypto
    {
        CUser* user;                  //0x00  0x13C
        Array<UINT8, 16> sessionKey;  //0x04  0x140
        bool isInitKey;               //0x14  0x150
        bool isInitPublicKey;         //0x15  0x151
        PAD(622);
        // 0x284
    };
    #pragma pack(pop)

    static_assert(sizeof(CUserCrypto) == 0x284);
}
