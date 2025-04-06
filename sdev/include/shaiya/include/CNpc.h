#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/AStar.h"
#include "include/shaiya/include/ChasePathList.h"
#include "include/shaiya/include/CObjectMoveable.h"
#include "include/shaiya/include/SNode.h"
#include "include/shaiya/include/Target.h"

namespace shaiya
{
    struct CUser;
    struct MapNpc;
    struct Npc;

    enum struct NpcStatus : int
    {
        Idle,
        Chase,
        FindTarget,
        ReturnHome
    };

    #pragma pack(push, 1)
    struct CNpc : SNode, CObjectMoveable
    {
        int32_t type;                 //0x34
        int32_t typeId;               //0x38
        int32_t angle;                //0x3C
        int32_t usingCount;           //0x40
        bool unknown;                 //0x44
        PAD(3);
        int32_t nextPos;              //0x48
        tick32_t nextMoveTime;        //0x4C
        Npc* info;                    //0x50
        MapNpc* posInfo;              //0x54
        NpcStatus status;             //0x58
        Target target;                //0x5C
        tick32_t nextChaseTime;       //0x64
        tick32_t disableTime;         //0x68
        AStar star;                   //0x6C
        ChasePathList chasePathList;  //0x94
        // 0x98

        static void SetTarget(CNpc* npc/*eax*/, CUser* user/*esi*/);
        static void StatusChange(CNpc* npc/*eax*/, int nextStatus/*ecx*/);
        static void StatusAttackStop(CNpc* npc/*eax*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CNpc) == 0x98);
}
