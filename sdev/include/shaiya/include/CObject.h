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
        // offsets: CObject, CUser
        SVector pos;   //0x00  0xD0
        ULONG id;      //0x0C  0xDC
        CZone* zone;   //0x10  0xE0
        UINT32 cellX;  //0x14  0xE4
        UINT32 cellZ;  //0x18  0xE8
        PAD(16);
        // 0x2C

        static void PSendViewCombat(CUser* user, void* data, int len);
        static void SendView(CObject* object/*ecx*/, void* data, int len/*edx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CObject) == 0x2C);
}
