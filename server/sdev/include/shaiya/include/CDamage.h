#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDamage
    {
        PAD(12);
        UINT16 skillId;   //0x0C
        PAD(2);
        UINT8 skillLv;    //0x10
        PAD(31);
        // user->id
        ULONG id;         //0x30
        //
    };
    #pragma pack(pop)
}
