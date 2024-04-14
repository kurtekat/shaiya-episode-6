#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    struct CCharacter;
    struct CMonster;
    struct CNpc;

    #pragma pack(push, 1)
    struct CWorldMgr
    {
        PAD(1310776);
        CCharacter* user;  //0x904AA0  0x140038
        PAD(9020);
        // 0x142378

        static CCharacter* FindUser(ULONG id/*CUser->id*/);
        static CMonster* FindMob(ULONG id/*CMob->id*/);
        static CNpc* FindNpc(ULONG id/*CNpc->id*/);
    };
    #pragma pack(pop)
}
