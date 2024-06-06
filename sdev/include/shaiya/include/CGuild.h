#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/SNode.h>
#include <shaiya/include/common/SSyncMap.h>
#include <shaiya/include/user/CharName.h>
#include <shaiya/include/user/GuildName.h>
#include "include/shaiya/include/CNpcData.h"

namespace shaiya
{
    struct CItem;

    using GuildRemark = std::array<char, 66>;
    using GuildWarehouse = std::array<CItem*, 240>;

    enum struct GuildPvPStatusType : UINT32
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
        UINT16 type;
        UINT16 level;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildPvP
    {
        GuildPvPStatusType statusType;  //0x4B4
        ULONG requestSenderId;          //0x4B8
        ULONG targetId;                 //0x4BC
        ULONG requestTargetId;          //0x4C0
        SVector area;                   //0x4C4
        UINT32 mapId;                   //0x4D0
        UINT32 userCount;               //0x4D4
        std::array<ULONG, 7> userList;  //0x4D8
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildUserInfo
    {
        SNode node;         //0x00
        ULONG charId;       //0x08
        CharName charName;  //0x0C
        PAD(3);
        Job job;            //0x24
        PAD(3);
        UINT16 level;       //0x28
        PAD(2);
        UINT8 rank;         //0x2C
        PAD(15);
        // 0x3C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CGuild
    {
        SNode node;                //0x00
        ULONG id;                  //0x08
        GuildName name;            //0x0C
        CharName masterName;       //0x25
        PAD(2);
        UINT32 officerCount;       //0x3C
        UINT32 country;            //0x40
        UINT32 points;             //0x44
        UINT32 rank;               //0x48
        UINT32 etin;               //0x4C
        UINT32 keepEtin;           //0x50
        bool hasHouse;             //0x54
        bool buyHouse;             //0x55
        GuildRemark remark;        //0x56
        UINT32 guildRankPoints;    //0x98
        UINT32 etinReturnCount;    //0x9C
        UINT32 grbJoinCount;       //0xA0
        GuildWarehouse warehouse;  //0xA4
        CRITICAL_SECTION cs464;    //0x464
        // 0x47C
        std::array<GuildNpc, 8> npcList;
        CRITICAL_SECTION cs49C;    //0x49C
        GuildPvP pvp;              //0x4B4
        // 0x4F4
        SSyncMap<ULONG, GuildUserInfo*> online;
        // 0x53C
        SSyncMap<ULONG, GuildUserInfo*> offline;
        // 0x584
        SSyncMap<ULONG, GuildUserInfo*> joinRequests;
        CRITICAL_SECTION cs5CC;    //0x5CC
        // 0x5E4

        static void Send(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
        static void SendAdmin(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
    };
    #pragma pack(pop)
}
