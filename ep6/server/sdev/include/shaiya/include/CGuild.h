#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CItem;

    #pragma pack(push, 1)
    struct CGuild
    {
        PAD(8);
        ULONG id;                //0x08
        char name[25];           //0x0C
        char bossName[21];       //0x25
        PAD(2);
        Count subBosses;         //0x3C
        UINT32 country;          //0x40
        UINT32 points;           //0x44
        UINT32 rank;             //0x48
        UINT32 etin;             //0x4C
        UINT32 keepEtin;         //0x50
        bool hasHouse;           //0x54
        bool buyHouse;           //0x55
        char remark[66];         //0x56
        UINT32 guildRankPoints;  //0x98
        UINT32 etinReturnCount;  //0x9C
        UINT32 grbJoinCount;     //0xA0
        CItem* warehouse[240];   //0xA4
        // 0x464
        PAD(196);
        Count enterUsers;        //0x528
        PAD(68);
        Count leaveUsers;        //0x570
        PAD(148);
        // 0x608

        static void Send(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
        static void SendAdmin(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
    };
    #pragma pack(pop)
}
