#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    struct Npc;
    struct CMap;
    struct CUser;

    #pragma pack(push, 1)
    enum struct NpcStatus : UINT32
    {
        Idle,
        Chase,
        FindTarget,
        ReturnHome
    };

    struct CNpc
    {
        SNode node;              //0x00
        SVector pos;             //0x08
        ULONG id;                //0x14
        CMap* map;               //0x18
        PAD(24);
        UINT32 type;             //0x34
        UINT32 typeId;           //0x38
        PAD(20);
        // cast this
        Npc* npcData;            //0x50
        PAD(4);
        NpcStatus status;        //0x58
        PAD(4);
        // CMob->id, CUser->id
        ULONG targetId;          //0x60
        PAD(4);
        DWORD lockOnTime;        //0x68
        PAD(44);
        // 0x98

        static void SetStatus(CNpc* npc/*eax*/, int status/*ecx*/);
        static void SetTarget(CNpc* npc/*eax*/, CUser* user/*esi*/);
        static void StatusChange(CNpc* npc/*eax*/, int nextStatus/*ecx*/);
        static void StatusAttackStop(CNpc* npc/*eax*/);
    };
    #pragma pack(pop)
}
