#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include <shaiya/include/common/SkillTypes.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include "include/main.h"
#include "include/shaiya/CMap.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/NetworkHelper.h"
#include "include/shaiya/SkillInfo.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

namespace user_skill
{
    int ability_70_hook1(CUser* user, SkillInfo* skillInfo)
    {
        auto abilityType1 = skillInfo->abilities[0].type;
        if (abilityType1 != SkillAbilityType::Frenzied)
            return 0;

        GameCharSkillUseOutgoing_EP6 outgoing{};
        outgoing.senderId = user->id;
        outgoing.targetId = user->id;
        outgoing.skillId = skillInfo->skillId;
        outgoing.skillLv = skillInfo->skillLv;

        if (!user->skillAbility70.triggered)
        {
            user->skillAbility70.triggered = true;
            user->skillAbility70.skillId = skillInfo->skillId;
            user->skillAbility70.skillLv = skillInfo->skillLv;
            user->skillAbility70.keepTime = GetTickCount() + (skillInfo->keepTime * 1000);

            outgoing.statusType = GameCharSkillUseStatusType::Triggered;
            NetworkHelper::Send(user, &outgoing, sizeof(GameCharSkillUseOutgoing_EP6));
        }
        else
        {
            user->skillAbility70.triggered = false;
            user->skillAbility70.skillId = 0;
            user->skillAbility70.skillLv = 0;
            user->skillAbility70.keepTime = 0;

            outgoing.statusType = GameCharSkillUseStatusType::Stopped;
            NetworkHelper::Send(user, &outgoing, sizeof(GameCharSkillUseOutgoing_EP6));
        }

        return 1;
    }

    int ability_70_hook2(CUser* user, SkillInfo* skillInfo)
    {
        auto abilityType1 = skillInfo->abilities[0].type;
        if (abilityType1 != SkillAbilityType::Frenzied)
            return 0;

        if (!user->skillAbility70.triggered)
            return 0;

        auto now = GetTickCount();
        if (now < user->skillAbility70.keepTime)
            return 1;

        user->skillAbility70.keepTime = now + (skillInfo->keepTime * 1000);

        auto abilityValue1 = skillInfo->abilities[0].value;
        auto damage = (user->health * abilityValue1) / 100;

        user->health -= damage;
        CUser::SendRecoverChange(user, user->health, user->stamina, user->mana);
        return 1;
    }

    void ability_70_hook3(CUser* user)
    {
        if (!user->skillAbility70.triggered)
            return;

        user->skillAbility70.triggered = false;
        user->skillAbility70.skillId = 0;
        user->skillAbility70.skillLv = 0;
        user->skillAbility70.keepTime = 0;

        GameCharSkillUseOutgoing_EP6 outgoing{};
        outgoing.senderId = user->id;
        outgoing.targetId = user->id;
        outgoing.skillId = user->skillAbility70.skillId;;
        outgoing.skillLv = user->skillAbility70.skillLv;
        outgoing.statusType = GameCharSkillUseStatusType::Stopped;
        NetworkHelper::Send(user, &outgoing, sizeof(GameCharSkillUseOutgoing_EP6));
    }

    void ability_70_hook4(CUser* user, SkillInfo* skillInfo)
    {
        auto abilityType1 = skillInfo->abilities[0].type;
        if (abilityType1 != SkillAbilityType::Frenzied)
            return;

        if (!user->skillAbility70.triggered)
            return;

        user->skillAbility70.triggered = false;
        user->skillAbility70.skillId = 0;
        user->skillAbility70.skillLv = 0;
        user->skillAbility70.keepTime = 0;

        GameCharSkillUseOutgoing_EP6 outgoing{};
        outgoing.senderId = user->id;
        outgoing.targetId = user->id;
        outgoing.skillId = user->skillAbility70.skillId;;
        outgoing.skillLv = user->skillAbility70.skillLv;
        outgoing.statusType = GameCharSkillUseStatusType::Stopped;
        NetworkHelper::Send(user, &outgoing, sizeof(GameCharSkillUseOutgoing_EP6));
    }

    /// <summary>
    /// Extends skill ability support. The abilityValue will be negative when a skill is removed.
    /// </summary>
    void set_ability_hook(CUser* user, int typeEffect, SkillAbilityType abilityType, int abilityValue)
    {
        switch (abilityType)
        {
        // itemId: 101112, 101113
        // skillId: 432
        case SkillAbilityType::MultiplyQuestExp:
            user->multiplyQuestExpRate += abilityValue;
            break;
        default:
            break;
        }
    }

    int multiply_exp(CUser* user, int exp, bool isQuest)
    {
        if (isQuest)
        {
            auto rate = user->multiplyQuestExpRate;
            if (rate <= 100)
                return exp;

            auto bonus = (rate / 100.0) * exp;
            return static_cast<int>(bonus);
        }

        auto multiplier = 1.0;
        auto rate = user->multiplyExp2;
        if (rate > 100)
            multiplier = rate / 100.0;

        switch (user->charmType)
        {
        case SkillCharmType::BlueDragon:
        case SkillCharmType::WhiteTiger:
        case SkillCharmType::RedPhoenix:
            multiplier += 0.2;
            break;
        default:
            break;
        }

        // expupmap

        auto zone = user->zone;
        if (zone)
        {
            auto map = zone->map;
            if (map)
            {
                multiplier *= map->expMultiplier;
            }
        }

        // expupcamp

        if (user->country == Country::Light)
            multiplier *= *reinterpret_cast<double*>(0x582768);
        else
            multiplier *= *reinterpret_cast<double*>(0x582770);

        auto bonus = multiplier * exp;
        return static_cast<int>(bonus);
    }
}

unsigned u0x45CCE9 = 0x45CCE9;
unsigned u0x45CD11 = 0x45CD11;
void __declspec(naked) naked_0x45CCE3()
{
    __asm
    {
        pushad

        push esi // skillInfo
        push ebp // sender
        call user_skill::ability_70_hook1
        add esp,0x8
        test eax,eax

        popad

        jne _0x45CD11

        // original
        mov ecx,[edi+0xDC]
        jmp u0x45CCE9

        _0x45CD11:
        jmp u0x45CD11
    }
}

unsigned u0x49606D = 0x49606D;
unsigned u0x4961F1 = 0x4961F1;
void __declspec(naked) naked_0x496067()
{
    __asm
    {
        pushad

        push ecx // skillInfo
        push esi // user
        call user_skill::ability_70_hook2
        add esp,0x8
        test eax,eax

        popad

        jne _0x4961F1

        // original
        mov edx,[ebp+0x08]
        cmp edx,[ebx+0x20]
        jmp u0x49606D
        
        _0x4961F1:
        jmp u0x4961F1
    }
}

unsigned u0x498623 = 0x498623;
void __declspec(naked) naked_0x49861D()
{
    __asm
    {
        pushad

        push esi // user
        call user_skill::ability_70_hook3
        add esp,0x4

        popad

        // original
        mov eax,[esi+0x1C4]
        jmp u0x498623
    }
}

unsigned u0x498882 = 0x498882;
void __declspec(naked) naked_0x49887C()
{
    __asm
    {
        pushad

        push esi // user
        call user_skill::ability_70_hook3
        add esp,0x4

        popad

        // original
        mov [esi+0x1348],ebx
        jmp u0x498882
    }
}

// CUser::ChkGetSkillPassive
unsigned u0x49A850 = 0x49A850;
unsigned u0x4935B7 = 0x4935B7;
void __declspec(naked) naked_0x4935B2()
{
    __asm
    {
        // original
        call u0x49A850

        pushad

        push esi // skillInfo
        push ebp // user
        call user_skill::ability_70_hook4
        add esp,0x8

        popad

        jmp u0x4935B7
    }
}

void __declspec(naked) naked_0x4959A4()
{
    __asm
    {
        pushad

        inc edx

        push eax // abilityValue
        push edx // abilityType
        push ecx // typeEffect
        push esi // user
        call user_skill::set_ability_hook
        add esp,0x10

        popad

        // original
        pop esi
        mov esp,ebp
        pop ebp
        retn 0x4
    }
}

unsigned u0x46511A = 0x46511A;
void __declspec(naked) naked_0x465087()
{
    __asm
    {
        pushad

        movzx eax,byte ptr[esp+0x44]
        mov ecx,dword ptr[esp+0x40]

        push eax // isQuest
        push ecx // exp
        push esi // user
        call user_skill::multiply_exp
        add esp,0xC

        mov dword ptr[esp+0x40],eax

        popad

        jmp u0x46511A
    }
}

void hook::user_skill()
{
    // CUser::SkillAttackRange
    util::detour((void*)0x45CCE3, naked_0x45CCE3, 6);
    // CUser::ChkEndTimeSkill
    util::detour((void*)0x496067, naked_0x496067, 6);
    // CUser::ClearApplySkillByDeath
    util::detour((void*)0x49861D, naked_0x49861D, 6);
    // CUser::SkillClearAll
    util::detour((void*)0x49887C, naked_0x49887C, 6);
    // CUser::LearnSkill
    util::detour((void*)0x4935B2, naked_0x4935B2, 5);
    // CUser::SetSkillAbility (default case)
    util::detour((void*)0x4959A4, naked_0x4959A4, 7);
    // CUser::AddExpFromUser
    util::detour((void*)0x465087, naked_0x465087, 5);
}
