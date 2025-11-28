#pragma once
#include <shaiya/include/common.h>
#include "common.h"
#include "CTexture.h"

namespace shaiya
{
    struct CCharacter;
    struct CMonster;
    struct CNpc;

    #pragma pack(push, 1)
    // 0x45A0F0 ctor
    struct CWorldMgr
    {
        PAD(1300868);               //0x7C4A68
        // max: 10000
        uint32_t effectCount;       //0x9023EC  0x13D988
        PAD(9904);
        CCharacter* user;           //0x904AA0  0x140038
        PAD(536);
        // F=2048, 70=1600, D=1024
        uint32_t mapSize;           //0x904CBC  0x140254
        PAD(332);
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
        PAD(8);
        // see Dungeon_MiniMap.cfg
        float mapImagePosX;         //0x904EB4  0x14044C
        float mapImagePosY;         //0x904EB8  0x140450
        PAD(7972);
        // 0x906DE0  0x142378

        static CCharacter* FindUser(unsigned objectId);
        static CMonster* FindMob(unsigned objectId);
        static CNpc* FindNpc(unsigned objectId);
        static void RenderEffect(int effectDataId, int effectSubId, D3DVECTOR* pos, D3DVECTOR* dir, D3DVECTOR* up, int unknown/*0:9*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CWorldMgr) == 0x142378);
    static auto g_pWorldMgr = (CWorldMgr*)0x7C4A68;
}
