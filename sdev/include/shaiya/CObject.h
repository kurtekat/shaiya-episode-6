#pragma once
#include <shaiya/include/common.h>
#include "CObjectLink.h"
#include "SVector.h"

namespace shaiya
{
    struct CUser;
    struct CZone;

    #pragma pack(push, 1)
    struct CObject
    {
        //                   this  CUser CItem CMob  CNpc
        SVector pos;       //0x00  0xD0  0x08  0x7C  0x08
        uint32_t id;       //0x0C  0xDC  0x14  0x88  0x14
        CZone* zone;       //0x10  0xE0  0x18  0x8C  0x18
        int32_t cellX;     //0x14  0xE4  0x1C  0x90  0x1C
        int32_t cellZ;     //0x18  0xE8  0x20  0x94  0x20
        CObjectLink link;  //0x1C  0xEC  0x24  0x98  0x24
        // 0x28

        static void PSendViewCombat(CUser* user, void* packet, int length);
        static void SendView(CObject* object/*ecx*/, void* packet, int length/*edx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CObject) == 0x28);
}
