#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "AttackAdd.h"
#include "AttackMob.h"
#include "AStar.h"
#include "ChasePathList.h"
#include "CDamageMob.h"
#include "CInterfaceAI.h"
#include "CObjectMoveable.h"
#include "SNode.h"
#include "SSyncList.h"
#include "StackStateMachine.h"
#include "SVector.h"
#include "Target.h"

namespace shaiya
{
    struct CDoor;
    struct CSkill;
    struct CUser;
    struct CZone;
    struct MobInfo;
    struct MobRespawn;
    struct SkillInfo;

    enum struct MobFuncType : int32_t
    {
        OnMoveEnd,
        OnAttacked,
        OnAttackable,
        OnNormalReset,
        OnDeath,
        OnReturnHome
    };

    enum struct MobStatus : int32_t
    {
        Idle,
        Chase,
        Death,
        ReturnHome,
        Unknown100 = 100
    };

    #pragma pack(push, 1)
    struct CMob : CInterfaceAI, StackStateMachine<CMob, -1>, SNode, CObjectMoveable
    {
        PAD(88);
        MobInfo* info;                       //0xD4
        PAD(208);
        MobStatus status;                    //0x1A8
        Target target;                       //0x1AC
        int32_t currentAttack;               //0x1B4
        AttackMob attack;                    //0x1B8
        AttackMob attackRanged;              //0x1D4
        AttackMob attackMagic;               //0x1F0
        AttackAdd attackAdd;                 //0x20C
        AttackAdd attackRangedAdd;           //0x21C
        AttackAdd attackMagicAdd;            //0x22C
        uint32_t attackTime1;                //0x23C
        uint32_t attackTime2;                //0x240
        uint32_t attackTime3;                //0x244
        SSyncList<CSkill> applySkills;       //0x248
        CDamageMob damage;                   //0x274
        uint32_t mobId;                      //0x2A4
        uint32_t health;                     //0x2A8
        uint16_t stamina;                    //0x2AC
        uint16_t mana;                       //0x2AE
        uint32_t dexterity;                  //0x2B0
        uint32_t wisdom;                     //0x2B4
        uint32_t luck;                       //0x2B8
        uint32_t attributeDefense;           //0x2BC
        uint32_t moveSpeed;                  //0x2C0
        uint32_t attackSpeed;                //0x2C4
        bool32_t immobilized;                //0x2C8
        bool32_t unconscious;                //0x2CC
        bool32_t sleeping;                   //0x2D0
        PAD(56);
        tick32_t retargetingTime;            //0x30C
        uint32_t attackedCount;              //0x310
        bool32_t onlyLuaAttack;              //0x314
        bool32_t holdPosition;               //0x318
        bool32_t unbeatable;                 //0x31C
        uint32_t luaOrderTime;               //0x320
        int32_t moveMode;                    //0x324
        SVector targetMovePos;               //0x328
        tick32_t lockOnTime;                 //0x334
        MobFuncType funcType;                //0x338
        PAD(2516);
        MobRespawn* respawn;                 //0xD10
        SVector respawnPos;                  //0xD14
        SVector exitPos;                     //0xD20
        SVector selectedPos;                 //0xD2C
        bool deathRemove;                    //0xD38
        PAD(3);
        tick32_t deathTime;                  //0xD3C
        tick32_t nextAttackTime;             //0xD40
        tick32_t nextChaseTime;              //0xD44
        tick32_t nextMoveTime;               //0xD48
        tick32_t nextMobCreateTime;          //0xD4C
        tick32_t nextTargetingTime;          //0xD50
        tick32_t nextNewTargetingTime;       //0xD54
        tick32_t nextRecoverTime;            //0xD58
        tick32_t currentTime;                //0xD5C
        SVector prevPos;                     //0xD60
        SVector moveDir;                     //0xD6C
        tick32_t prevMoveTime;               //0xD78
        float moveRange;                     //0xD7C
        PAD(28);
        CRITICAL_SECTION cs;                 //0xD9C
        String<32> prevAttackCharName;       //0xDB4
        String<32> prevAttackSkillName;      //0xDD4
        // 0xDF4
        
        static bool IsBossMob(CMob* mob/*eax*/);
        static bool IsObelisk(CMob* mob/*eax*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CMob) == 0xDF4);
}
