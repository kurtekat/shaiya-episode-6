#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>
#include "GuildUserInfo.h"
#include "SNode.h"
#include "SSyncMap.h"
#include "SVector.h"

namespace shaiya
{
    struct CItem;
    struct CUser;

    enum struct GuildPvPStatus : int32_t
    {
        None,
        RequestSent,
        RequestRecv,
        Countdown,
        Start
    };

    #pragma pack(push, 1)
    struct GuildNpc
    {
        uint16_t type;
        uint16_t level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CGuild : SNode
    {
        uint32_t id;                   //0x08
        String<25> name;               //0x0C
        String<21> masterName;         //0x25
        PAD(2);
        int32_t adminCount;            //0x3C
        int32_t country;               //0x40
        uint32_t rankPoints;           //0x44
        uint32_t rank;                 //0x48
        uint32_t etin;                 //0x4C
        uint32_t keepEtin;             //0x50
        bool hasHouse;                 //0x54
        bool buyHouse;                 //0x55
        String<65> remark;             //0x56
        PAD(1);
        uint32_t grbPoints;            //0x98
        uint32_t etinReturnCount;      //0x9C
        uint32_t grbJoinCount;         //0xA0
        Array<CItem*, 240> warehouse;  //0xA4
        CRITICAL_SECTION csWarehouse;  //0x464
        Array<GuildNpc, 8> npcs;       //0x47C
        CRITICAL_SECTION csNpcs;       //0x49C
        GuildPvPStatus pvpStatus;      //0x4B4
        uint32_t pvpMasterId;          //0x4B8
        uint32_t pvpGuildId;           //0x4BC
        uint32_t pvpGuildMasterId;     //0x4C0
        SVector pvpPos;                //0x4C4
        int32_t pvpMapId;              //0x4D0
        int32_t pvpUserCount;          //0x4D4
        Array<uint32_t, 7> pvpUsers;   //0x4D8
        // 0x4F4
        SSyncMap<uint32_t, GuildUserInfo*> online;
        // 0x53C
        SSyncMap<uint32_t, GuildUserInfo*> offline;
        // 0x584
        SSyncMap<uint32_t, GuildUserInfo*> join;
        CRITICAL_SECTION cs;           //0x5CC
        // 0x5E4

        static void Send(CGuild* guild, void* packet/*ecx*/, int length/*eax*/);
        static void SendAdmin(CGuild* guild, void* packet/*ecx*/, int length/*eax*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CGuild) == 0x5E4);
}
