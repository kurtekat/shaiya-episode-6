#pragma once
#include <shaiya/include/common.h>
#include "SAes.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CUserCrypto
    {
        SAes aesDec;    //0x00
        SAes aesEnc;    //0x118
        bool initDec;   //0x230
        bool initEnc;   //0x231
        bool initGame;  //0x232
        PAD(1);
        // 0x234
    };
    #pragma pack(pop)

    static_assert(sizeof(CUserCrypto) == 0x234);
}
