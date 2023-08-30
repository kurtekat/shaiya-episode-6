#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    FWDDECL CDoor;
    FWDDECL CUser;
    FWDDECL CZone;

    #pragma pack(push, 1)
    struct MobRespawn
    {
        PAD(12);
        TickCount time;      //0x0C
        PAD(4);
        BOOL isObelisk;      //0x14
        PAD(4);
        BOOL isBossMob;      //0x1C
        PAD(76);
        TickCount cooldown;  //0x6C
        PAD(36);
        SVector pos;         //0x94
        float radius;        //0xA0
        //
    };

    struct MapBossMob
    {
        UINT32 index;        //0x00
        UINT32 count;        //0x04
        // value * 1000
        TickCount cooldown;  //0x08
        UINT32 mapId;        //0x0C
        UINT32 portalId;     //0x10
        CDoor* portal;       //0x14
        PAD(4);
        SVector pos;         //0x1C
        //
    };

    enum struct LuaEvent : UINT32
    {
        OnMoveEnd,
        OnAttacked,
        OnAttackable,
        OnNormalReset,
        OnDeath,
        OnReturnHome
    };

    struct CMob
    {
        PAD(124);
        SVector pos;             //0x7C
        ULONG id;                //0x88
        CZone* zone;             //0x8C
        PAD(68);
        //0xD4
        CGameData::MobInfo* mobInfo;
        PAD(208);
        UINT32 status;           //0x1A8
        PAD(4);
        ULONG attackerId;        //0x1B0
        PAD(240);
        UINT32 mobId;            //0x2A4
        UINT32 health;           //0x2A8
        UINT16 stamina;          //0x2AC
        UINT16 mana;             //0x2AE
        UINT32 dexterity;        //0x2B0
        UINT32 wisdom;           //0x2B4
        UINT32 luck;             //0x2B8
        UINT32 attribute;        //0x2BC
        UINT32 moveSpeed;        //0x2C0
        UINT32 attackSpeed;      //0x2C4
        PAD(64);
        ULONG luaCharId;         //0x308
        PAD(44);
        LuaEvent luaEvent;       //0x338
        PAD(2516);
        MobRespawn* mobRespawn;  //0xD10
        PAD(40);
        // 004A1A53
        TickCount destroyTime;   //0xD3C
        //

        static int GetCountry(CMob* mob/*eax*/);
        static void UseSkill(CMob* mob/*edi*/, TickCount time, CUser* user/*edx*/, CGameData::SkillInfo* info/*eax*/);
        static bool EnableApplyRangeItem(CUser* base/*eax*/, CUser* user/*ecx*/);
    };
    #pragma pack(pop)
}
