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
        CCharacter* user;           //0x904AA0  0x140038
        PAD(872);
        CTexture attribute0Image;   //0x904E0C  0x1403A4  mon_not_ex.tga
        CTexture attribute1Image;   //0x904E1C  0x1403B4  mon_fire_ex.tga
        CTexture attribute2Image;   //0x904E2C  0x1403C4  mon_water_ex.tga
        CTexture attribute3Image;   //0x904E3C  0x1403D4  mon_ground_ex.tga
        CTexture attribute4Image;   //0x904E4C  0x1403E4  mon_wind_ex.tga
        CTexture questImage;        //0x904E5C  0x1403F4  mon_quest_ex.tga
        CTexture partyMemberImage;  //0x904E6C  0x140404  party_member.tga
        CTexture partyLeaderImage;  //0x904E7C  0x140414  party_jang.tga
        CTexture pvpGradeImage;     //0x904E8C  0x140424  grade2.tga
        CTexture pvpArrowImage;     //0x904E9C  0x140434  pvp_arrow.tga
        // 0x904EAC  0x140444
        PAD(7988);
        // 0x906DE0  0x142378

        static CCharacter* FindUser(ULONG id/*CUser->id*/);
        static CMonster* FindMob(ULONG id/*CMob->id*/);
        static CNpc* FindNpc(ULONG id/*CNpc->id*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CWorldMgr) == 0x142378);
    static auto g_pWorldMgr = (CWorldMgr*)0x7C4A68;
}
