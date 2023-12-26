#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CNpcData.h>
#include <include/shaiya/include/SNode.h>
#include <include/shaiya/include/SSyncMap.h>

namespace shaiya
{
    struct CItem;

    typedef Array<char, 66> GuildRemark;

    #pragma pack(push, 1)
    enum struct GuildPvPState : UINT32
    {
        None,
        RequestSent,
        RequestRecv,
        Countdown,
        Start
    };

    struct GuildNpc
    {
        NpcType type;
        UINT8 level;
        UINT8 number;
    };

    struct GuildPvP
    {
        GuildPvPState state;        //0x4B4
        CharId requestSenderId;     //0x4B8
        GuildId targetId;           //0x4BC
        CharId requestTargetId;     //0x4C0
        SVector area;               //0x4C4
        UINT32 mapId;               //0x4D0
        UINT32 userCount;           //0x4D4
        Array<CharId, 7> userList;  //0x4D8
    };

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

    typedef SSyncMap<ULONG, GuildUserInfo*> GuildUserInfoMap;

    struct CGuild
    {
        SNode node;                 //0x00
        GuildId id;                 //0x08
        GuildName name;             //0x0C
        CharName masterName;        //0x25
        PAD(2);
        UINT32 officerCount;        //0x3C
        UINT32 country;             //0x40
        UINT32 points;              //0x44
        UINT32 rank;                //0x48
        UINT32 etin;                //0x4C
        UINT32 keepEtin;            //0x50
        bool hasHouse;              //0x54
        bool buyHouse;              //0x55
        GuildRemark remark;         //0x56
        UINT32 guildRankPoints;     //0x98
        UINT32 etinReturnCount;     //0x9C
        UINT32 grbJoinCount;        //0xA0
        Warehouse warehouse;        //0xA4
        CRITICAL_SECTION cs464;     //0x464
        Array<GuildNpc, 8> npc;     //0x47C
        CRITICAL_SECTION cs49C;     //0x49C
        GuildPvP pvp;               //0x4B4
        GuildUserInfoMap enterMap;  //0x4F4
        GuildUserInfoMap leaveMap;  //0x53C
        GuildUserInfoMap joinMap;   //0x584
        CRITICAL_SECTION cs5CC;     //0x5CC
        // 0x5E4

        static int GetNumUsers(CGuild* guild/*ecx*/);
        static void Send(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
        static void SendAdmin(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
    };
    #pragma pack(pop)
}
