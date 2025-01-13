#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common/SkillTypes.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/SkillInfo.h"
#include "include/shaiya/include/network/game/outgoing/0500.h"
using namespace shaiya;

namespace user_skill
{
    int ability_70_hook1(CUser* user, SkillInfo* skillInfo)
    {
        auto abilityType1 = skillInfo->abilities[0].type;
        if (abilityType1 != SkillAbilityType::Frenzied)
            return 0;

        UserSkillUseOutgoing_EP6 outgoing{};
        outgoing.senderId = user->connection.object.id;
        outgoing.targetId = user->connection.object.id;
        outgoing.skillId = skillInfo->skillId;
        outgoing.skillLv = skillInfo->skillLv;

        if (!user->skillAbility70.triggered)
        {
            outgoing.status = UserSkillUseStatus::Triggered;

            user->skillAbility70.triggered = true;
            user->skillAbility70.skillId = skillInfo->skillId;
            user->skillAbility70.skillLv = skillInfo->skillLv;
            user->skillAbility70.keepTick = GetTickCount() + (skillInfo->keepTime * 1000);

            NetworkHelper::Send(user, &outgoing, sizeof(UserSkillUseOutgoing_EP6));
        }
        else
        {
            outgoing.status = UserSkillUseStatus::Stopped;

            user->skillAbility70.triggered = false;
            user->skillAbility70.skillId = 0;
            user->skillAbility70.skillLv = 0;
            user->skillAbility70.keepTick = 0;

            NetworkHelper::Send(user, &outgoing, sizeof(UserSkillUseOutgoing_EP6));
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
        if (now < user->skillAbility70.keepTick)
            return 1;

        user->skillAbility70.keepTick = now + (skillInfo->keepTime * 1000);

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

        auto skillId = user->skillAbility70.skillId;
        auto skillLv = user->skillAbility70.skillLv;

        UserSkillUseOutgoing_EP6 outgoing{};
        outgoing.senderId = user->connection.object.id;
        outgoing.targetId = user->connection.object.id;
        outgoing.skillId = skillId;
        outgoing.skillLv = skillLv;
        outgoing.status = UserSkillUseStatus::Stopped;

        user->skillAbility70.triggered = false;
        user->skillAbility70.skillId = 0;
        user->skillAbility70.skillLv = 0;
        user->skillAbility70.keepTick = 0;

        NetworkHelper::Send(user, &outgoing, sizeof(UserSkillUseOutgoing_EP6));
    }

    void ability_70_hook4(CUser* user, SkillInfo* skillInfo)
    {
        auto abilityType1 = skillInfo->abilities[0].type;
        if (abilityType1 != SkillAbilityType::Frenzied)
            return;

        if (!user->skillAbility70.triggered)
            return;

        auto skillId = user->skillAbility70.skillId;
        auto skillLv = user->skillAbility70.skillLv;

        UserSkillUseOutgoing_EP6 outgoing{};
        outgoing.senderId = user->connection.object.id;
        outgoing.targetId = user->connection.object.id;
        outgoing.skillId = skillId;
        outgoing.skillLv = skillLv;
        outgoing.status = UserSkillUseStatus::Stopped;

        user->skillAbility70.triggered = false;
        user->skillAbility70.skillId = 0;
        user->skillAbility70.skillLv = 0;
        user->skillAbility70.keepTick = 0;

        NetworkHelper::Send(user, &outgoing, sizeof(UserSkillUseOutgoing_EP6));
    }

    /// <summary>
    /// Extends skill ability support.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="typeEffect"></param>
    /// <param name="abilityType"></param>
    /// <param name="abilityValue">The value will be negative in the case of removal.</param>
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
}
