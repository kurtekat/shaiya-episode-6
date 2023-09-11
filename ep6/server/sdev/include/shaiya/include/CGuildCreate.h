#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        PAD(36);
        UINT32 joinCount;   //0x24
        UINT32 bossId;      //0x28
        CUser* boss;        //0x2C
        CharId members[7];  //0x30
        // 0x4C
        PAD(28);
        // 0x68
    };
    #pragma pack(pop)
}
