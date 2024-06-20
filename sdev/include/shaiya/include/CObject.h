#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CUser;
    struct CZone;

    #pragma pack(push, 1)
    struct CObject
    {
        SVector pos;   //0x00
        PAD(4);
        CZone* zone;   //0x10
        UINT32 cellX;  //0x14
        UINT32 cellZ;  //0x18
        PAD(16);
        // 0x2C

        static void PSendViewCombat(CUser* user, void* data, int len);
    };
    #pragma pack(pop)
}
