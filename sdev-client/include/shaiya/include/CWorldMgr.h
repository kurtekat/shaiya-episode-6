#pragma once
#include "include/shaiya/common.h"
#include "include/shaiya/include/CTexture.h"

namespace shaiya
{
    struct CCharacter;
    struct CMonster;
    struct CNpc;

    #pragma pack(push, 1)
    // 0x45A0F0 ctor
    struct CWorldMgr
    {
        PAD(1310776);
        CCharacter* user;        //0x904AA0  0x140038
        PAD(872);
        CTexture mon_not_ex;     //0x904E0C  0x1403A4
        CTexture mon_fire_ex;    //0x904E1C  0x1403B4
        CTexture mon_water_ex;   //0x904E2C  0x1403C4
        CTexture mon_ground_ex;  //0x904E3C  0x1403D4
        CTexture mon_wind_ex;    //0x904E4C  0x1403E4
        CTexture mon_quest_ex;   //0x904E5C  0x1403F4
        CTexture party_member;   //0x904E6C  0x140404
        CTexture party_jang;     //0x904E7C  0x140414
        CTexture grade2;         //0x904E8C  0x140424
        CTexture pvp_arrow;      //0x904E9C  0x140434
        // 0x904EAC  0x140444
        PAD(7988);
        // 0x906DE0  0x142378

        static CCharacter* FindUser(ULONG id/*CUser->id*/);
        static CMonster* FindMob(ULONG id/*CMob->id*/);
        static CNpc* FindNpc(ULONG id/*CNpc->id*/);
    };
    #pragma pack(pop)

    inline auto g_pWorldMgr = (CWorldMgr*)0x7C4A68;
}
