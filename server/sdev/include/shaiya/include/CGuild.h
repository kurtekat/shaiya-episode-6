#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CNpcData.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    FWDDECL CItem;

    typedef Array<char, 66> GuildRemark;

    #pragma pack(push, 1)
    enum struct GvGState : UINT32
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

    struct CGuild
    {
        SNode node;                   //0x00
        GuildId id;                   //0x08
        GuildName name;               //0x0C
        CharName leaderName;          //0x25
        PAD(2);
        UINT32 numSubLeaders;         //0x3C
        UINT32 country;               //0x40
        UINT32 points;                //0x44
        UINT32 rank;                  //0x48
        UINT32 etin;                  //0x4C
        UINT32 keepEtin;              //0x50
        bool hasHouse;                //0x54
        bool buyHouse;                //0x55
        GuildRemark remark;           //0x56
        UINT32 guildRankPoints;       //0x98
        UINT32 etinReturnCount;       //0x9C
        UINT32 grbJoinCount;          //0xA0
        Array<CItem*, 240> warehouse; //0xA4
        CRITICAL_SECTION cs464;       //0x464
        Array<GuildNpc, 8> npc;       //0x47C
        CRITICAL_SECTION cs49C;       //0x49C
        GvGState gvgState;            //0x4B4
        CharId gvgRequestSenderId;    //0x4B8
        GuildId gvgTargetId;          //0x4BC
        CharId gvgRequestTargetId;    //0x4C0
        PAD(100);
        UINT32 numEnterUsers;         //0x528
        PAD(68);
        UINT32 numLeaveUsers;         //0x570
        PAD(148);
        // 0x608

        static void Send(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
        static void SendAdmin(CGuild* guild, void* data/*ecx*/, int len/*eax*/);
    };
    #pragma pack(pop)
}
