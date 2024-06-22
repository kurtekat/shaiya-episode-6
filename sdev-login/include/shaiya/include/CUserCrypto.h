#pragma once
#include <bitset>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CUserCrypto
    {
        CUser* user;           //0x00  0x13C
        // 0x04  0x140
        std::bitset<128> sessionKey;   
        bool isInitKey;        //0x14  0x150
        bool isInitPublicKey;  //0x15  0x151
        PAD(622);
        // 0x284
    };
    #pragma pack(pop)
}
