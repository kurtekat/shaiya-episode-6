#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/CDamageMob.h"
#include "include/shaiya/include/CObject.h"
#include "include/shaiya/include/SNode.h"
#include "include/shaiya/include/SSyncList.h"
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CDoor;
    struct CSkill;
    struct CUser;
    struct CZone;
    struct MobInfo;
    struct SkillInfo;

    #pragma pack(push, 1)
    struct stMobRespawn
    {
        UINT32 mobId;    //0x00
        PAD(8);
        DWORD tick;      //0x0C
        PAD(4);
        BOOL isObelisk;  //0x14
        PAD(4);
        BOOL isBossMob;  //0x1C
        PAD(4);
        // 0x24
    };
    #pragma pack(pop)

    static_assert(sizeof(stMobRespawn) == 0x24);

    enum struct MobLuaEvent : UINT32
    {
        OnMoveEnd,
        OnAttacked,
        OnAttackable,
        OnNormalReset,
        OnDeath,
        OnReturnHome
    };

    enum struct MobStatus : UINT32
    {
        Idle,
        Chase,
        Death,
        ReturnHome,
        Unknown100 = 100
    };

    #pragma pack(push, 1)
    struct CMob
    {
        void* vftable1;                    //0x00
        void* vftable2;                    //0x04
        PAD(116);
        CObjectMoveable moveable;          //0x7C
        // 0xA8
        PAD(44);
        MobInfo* mobInfo;                  //0xD4
        PAD(208);
        MobStatus status;                  //0x1A8
        PAD(4);
        ULONG targetId;                    //0x1B0
        PAD(4);
        BOOL attackBlinded;                //0x1B8
        UINT32 hitRate;                    //0x1BC
        UINT32 addAttackPower;             //0x1C0
        UINT32 evasionRate;                //0x1C4
        UINT32 defense;                    //0x1C8
        UINT32 criticalHitRate;            //0x1CC
        PAD(4);
        BOOL rangedAttackBlinded;          //0x1D4
        UINT32 rangedHitRate;              //0x1D8
        UINT32 addRangedAttackPower;       //0x1DC
        UINT32 rangedEvasionRate;          //0x1E0
        UINT32 rangedDefense;              //0x1E4
        UINT32 rangedCriticalHitRate;      //0x1E8
        PAD(4);
        BOOL silenced;                     //0x1F0
        UINT32 magicHitRate;               //0x1F4
        UINT32 addMagicPower;              //0x1F8
        UINT32 magicEvasionRate;           //0x1FC
        UINT32 magicResistance;            //0x200
        UINT32 magicCriticalHitRate;       //0x204
        PAD(4);
        UINT32 abilityAddHitRate;          //0x20C
        UINT32 abilityAddAttackPower;      //0x210
        UINT32 abilityAddEvasionRate;      //0x214
        UINT32 abilityAddDefense;          //0x218
        PAD(12);
        UINT32 abilityAddRangedDefense;    //0x228
        PAD(12);
        UINT32 abilityAddMagicResistance;  //0x238
        PAD(12);
        SSyncList<CSkill> applySkills;     //0x248
        CDamageMob damageMob;              //0x274
        UINT32 mobId;                      //0x2A4
        UINT32 health;                     //0x2A8
        UINT16 stamina;                    //0x2AC
        UINT16 mana;                       //0x2AE
        UINT32 dexterity;                  //0x2B0
        UINT32 wisdom;                     //0x2B4
        UINT32 luck;                       //0x2B8
        UINT32 attribute;                  //0x2BC
        UINT32 moveSpeed;                  //0x2C0
        UINT32 attackSpeed;                //0x2C4
        BOOL immobilized;                  //0x2C8
        BOOL unconscious;                  //0x2CC
        BOOL sleeping;                     //0x2D0
        PAD(52);
        ULONG luaTargetId;                 //0x308
        DWORD retargetingTerm;             //0x30C
        PAD(4);
        BOOL onlyLuaAttack;                //0x314
        BOOL holdPosition;                 //0x318
        BOOL unbeatable;                   //0x31C
        PAD(20);
        DWORD lockOnTick;                  //0x334
        MobLuaEvent luaEvent;              //0x338
        PAD(2516);
        stMobRespawn* mobRespawn;          //0xD10
        PAD(40);
        DWORD destroyTick;                 //0xD3C
        PAD(92);
        CRITICAL_SECTION cs;               //0xD9C
        // gameLog
        CharArray<32> text3;               //0xDB4
        CharArray<32> text4;               //0xDD4
        // 0xDF4
        
        static bool IsBossMob(CMob* mob/*eax*/);
        static bool IsObelisk(CMob* mob/*eax*/);
        static void UseSkill(CMob* mob/*edi*/, ULONG time, CUser* user/*edx*/, SkillInfo* info/*eax*/);
        static void SendLogBossMob(CMob* mob/*edx*/, UINT byAction, const char* text3/*edi*/, const char* text4, ULONG damage);
        static void SetAttack(CMob* mob/*esi*/);
        static void SetStatus(CMob* mob/*eax*/, int status/*ecx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CMob) == 0xDF4);
}
