#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>
#include <shaiya/include/item/ItemDivType.h>

namespace shaiya
{
    struct CUser;

    struct PartyMember
    {
        UINT32 index;
        CUser* user;
    };

    #pragma pack(push, 1)
    struct CParty
    {
        SNode node;               //0x00
        ULONG id;                 //0x08
        UINT32 leaderIndex;       //0x0C
        UINT32 memberCount;       //0x10
        // 0x14
        Array<PartyMember, 30> memberList;
        ItemDivType itemDivType;  //0x104
        UINT32 itemDivSeq;        //0x108
        UINT32 topMemberLevel;    //0x10C
        UINT32 subLeaderIndex;    //0x110
        bool isUnion;             //0x114
        bool isAutoJoin;          //0x115
        PAD(2);
        CRITICAL_SECTION cs118;   //0x118
        // 0x130

        static CUser* FindUser(CParty* party/*edi*/, ULONG id/*CUser->id*/);
        static bool IsPartyBoss(CParty* party/*esi*/, CUser* user);
        static bool IsPartySubBoss(CParty* party/*esi*/, CUser* user);
        static CUser* GetPartyBoss(CParty* party/*esi*/);
        static CUser* GetPartySubBoss(CParty* party/*esi*/);
        static void LeaveParty(CUser* user/*eax*/, CParty* party/*ecx*/);
        static void Send(CParty* party/*esi*/, void* data/*ecx*/, int len/*eax*/);
    };
    #pragma pack(pop)
}
