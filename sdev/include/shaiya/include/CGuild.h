#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>
#include "include/shaiya/include/SNode.h"
#include "include/shaiya/include/SSyncMap.h"
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CItem;

    #pragma pack(push, 1)
    struct GuildNpc
    {
        UINT16 type;
        UINT16 level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildNpcs
    {
        Array<GuildNpc, 8> npcs;  //0x47C
        CRITICAL_SECTION cs;      //0x49C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildPvP
    {
        enum struct 
            Status : UINT32
        {
            None,
            RequestSent,
            RequestReceived,
            Countdown,
            Start
        } status;                 //0x4B4
        ULONG requestSenderId;    //0x4B8
        ULONG targetId;           //0x4BC
        ULONG requestTargetId;    //0x4C0
        SVector area;             //0x4C4
        UINT32 mapId;             //0x4D0
        UINT32 memberCount;       //0x4D4
        Array<ULONG, 7> members;  //0x4D8
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildWarehouse
    {
        Array<CItem*, 240> items;  //0xA4
        CRITICAL_SECTION cs;       //0x464
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct stGuildUserInfo
    {
        SNode node;              //0x00
        ULONG charId;            //0x08
        CharArray<21> charName;  //0x0C
        PAD(3);
        Job job;                 //0x24
        PAD(3);
        UINT16 level;            //0x28
        PAD(2);
        UINT8 rank;              //0x2C
        PAD(15);
        // 0x3C
    };
    #pragma pack(pop)

    static_assert(sizeof(stGuildUserInfo) == 0x3C);

    #pragma pack(push, 1)
    struct GuildMembers
    {
        SSyncMap<ULONG, stGuildUserInfo*> online;   //0x4F4
        SSyncMap<ULONG, stGuildUserInfo*> offline;  //0x53C
        SSyncMap<ULONG, stGuildUserInfo*> joiners;  //0x584
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CGuild
    {
        SNode node;                //0x00
        ULONG id;                  //0x08
        CharArray<25> name;        //0x0C
        CharArray<21> masterName;  //0x25
        PAD(2);
        UINT32 adminCount;         //0x3C
        UINT32 country;            //0x40
        UINT32 points;             //0x44
        UINT32 rank;               //0x48
        UINT32 etin;               //0x4C
        UINT32 keepEtin;           //0x50
        bool hasHouse;             //0x54
        bool buyHouse;             //0x55
        CharArray<66> remark;      //0x56
        UINT32 guildRankPoints;    //0x98
        UINT32 etinReturnCount;    //0x9C
        UINT32 grbJoinCount;       //0xA0
        GuildWarehouse warehouse;  //0xA4
        GuildNpcs npcs;            //0x47C
        GuildPvP pvp;              //0x4B4
        GuildMembers members;      //0x4F4
        CRITICAL_SECTION cs;       //0x5CC
        // 0x5E4

        static void Send(CGuild* guild, void* packet/*ecx*/, int length/*eax*/);
        static void SendAdmin(CGuild* guild, void* packet/*ecx*/, int length/*eax*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CGuild) == 0x5E4);
}
