#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/NpcType.h>
#include <shaiya/include/SNode.h>
#include "include/shaiya/include/CObject.h"
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct Npc;
    struct CMap;
    struct CUser;

    enum struct NpcStatus : UINT32
    {
        Idle,
        Chase,
        FindTarget,
        ReturnHome
    };

    #pragma pack(push, 1)
    struct CNpc
    {
        SNode node;        //0x00
        // 0x08
        CObjectMoveable moveable;
        NpcType32 type;    //0x34
        UINT32 typeId;     //0x38
        PAD(20);
        // cast this
        Npc* npcData;      //0x50
        PAD(4);
        NpcStatus status;  //0x58
        PAD(4);
        ULONG targetId;    //0x60
        PAD(4);
        DWORD lockOnTick;  //0x68
        PAD(44);
        // 0x98

        static void SetStatus(CNpc* npc/*eax*/, int status/*ecx*/);
        static void SetTarget(CNpc* npc/*eax*/, CUser* user/*esi*/);
        static void StatusChange(CNpc* npc/*eax*/, int nextStatus/*ecx*/);
        static void StatusAttackStop(CNpc* npc/*eax*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CNpc) == 0x98);
}
