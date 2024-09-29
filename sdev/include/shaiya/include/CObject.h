#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SConnection.h"
#include "include/shaiya/include/SSyncQueueBufferPriority.h"
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CUser;
    struct CZone;

    #pragma pack(push, 1)
    struct CObject
    {
        SVector pos;   //0x00  CUser+0xD0  CItem+0x08  CMob+0x7C  CNpc+0x08
        ULONG id;      //0x0C  CUser+0xDC  CItem+0x14  CMob+0x88  CNpc+0x14
        CZone* zone;   //0x10  CUser+0xE0  CItem+0x18  CMob+0x8C  CNpc+0x18
        UINT32 cellX;  //0x14  CUser+0xE4  CItem+0x1C  CMob+0x90  CNpc+0x1C
        UINT32 cellZ;  //0x18  CUser+0xE8  CItem+0x20  CMob+0x94  CNpc+0x20
        PAD(12);
        // 0x28

        static void PSendViewCombat(CUser* user, void* packet, int length);
        static void SendView(CObject* object/*ecx*/, void* packet, int length/*edx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CObject) == 0x28);

    #pragma pack(push, 1)
    struct CObjectConnection
    {
        SConnection connection;        //0x00
        CObject object;                //0xD0
        SSyncQueueBufferPriority qbp;  //0xFC
        PAD(8);
        // 0x128
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectConnection) == 0x128);

    #pragma pack(push, 1)
    // thanks, Cups :P
    struct CObjectMoveable
    {
        CObject object;    //0x00
        UINT32 moveCount;  //0x28
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectMoveable) == 0x2C);
}
