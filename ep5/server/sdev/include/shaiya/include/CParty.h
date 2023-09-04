#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    enum struct ItemDivType : UINT32
    {
        Group = 1,
        Random,
        Unknown,
        Master
    };

    struct PartySlot
    {
        UINT32 index;
        CUser* user;
    };

    struct CParty
    {
        PAD(8);
        ULONG id;                 //0x08
        UINT32 bossIndex;         //0x0C
        UINT32 count;             //0x10
        PartySlot slot[30];       //0x14
        ItemDivType itemDivType;  //0x104
        UINT32 itemDivSeq;        //0x108
        UINT32 level;             //0x10C
        UINT32 subBossIndex;      //0x110
        bool isUnion;             //0x114
        bool isAutoJoin;          //0x115
        PAD(2);
        // 0x118

        static CUser* FindUser(CParty* party/*edi*/, ULONG id/*CUser->id*/);
        static void LeaveParty(CUser* user/*eax*/, CParty* party/*ecx*/);
        static void Send(CParty* party/*esi*/, void* data/*ecx*/, int len/*eax*/);
    };
    #pragma pack(pop)
}
