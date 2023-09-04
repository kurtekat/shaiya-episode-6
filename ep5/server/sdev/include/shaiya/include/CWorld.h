#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CMap;
    FWDDECL CUser;
    FWDDECL CZone;

    #pragma pack(push, 1)
    struct KCStatus
    {
        UINT32 index;      //0x00
        UINT32 killCount;  //0x04
        UINT32 nextGrade;  //0x08
        PAD(120);
        // 0x84
    };

    struct CWorld
    {
        PAD(8);
        Count maps;            //0x08
        CMap* map;             //0x0C
        PAD(568);
        KCStatus kcStatus[2];  //0x248
        // 0x350

        static CUser* FindUser(ULONG id/*CUser->id*/);
        static CUser* FindUser(PCSTR charName/*eax*/);
        static CZone* GetZone(int mapId/*eax*/);
        static void SendAll(void* data/*ecx*/, int len/*eax*/);
        static void SendAllCountry(void* data/*ecx*/, int len/*eax*/, int country);
    };
    #pragma pack(pop)

    //0x587960
    static CWorld* g_pWorld = (CWorld*)0x10A2018; //0x587960
}
