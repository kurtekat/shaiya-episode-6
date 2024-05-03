#pragma warning(disable: 28159) // GetTickCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common/SkillAbilityType.h>
#include <shaiya/include/common/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CSkill.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CZone.h"
#include "include/shaiya/include/SkillInfo.h"
#include "include/shaiya/include/network/game/outgoing/0500.h"
using namespace shaiya;

namespace user_apply_skill
{
    void ability_70_handler(CUser* user, SkillInfo* skillInfo)
    {
        SkillUseOutgoing outgoing{};
        outgoing.senderId = user->id;
        outgoing.targetId = user->id;
        outgoing.skillId = skillInfo->skillId;
        outgoing.skillLv = skillInfo->skillLv;

        if (!user->skillAbility.type70.triggered)
        {
            outgoing.statusType = SkillUseStatusType::Triggered;

            user->skillAbility.type70.triggered = true;
            user->skillAbility.type70.skillId = outgoing.skillId;
            user->skillAbility.type70.skillLv = outgoing.skillLv;
            user->skillAbility.type70.keepTick = GetTickCount() + (skillInfo->keepTime * 1000);

            SConnection::Send(&user->connection, &outgoing, sizeof(SkillUseOutgoing));
            CUser::AddApplySkillBuff(user, skillInfo);
        }
        else
        {
            outgoing.statusType = SkillUseStatusType::Stopped;

            user->skillAbility.type70.triggered = false;
            user->skillAbility.type70.skillId = 0;
            user->skillAbility.type70.skillLv = 0;
            user->skillAbility.type70.keepTick = 0;

            SConnection::Send(&user->connection, &outgoing, sizeof(SkillUseOutgoing));
            CUser::RemApplySkillBuff(user, skillInfo);
        }
    }

    void ability_70_check_apply(CUser* user)
    {
        if (user->status == UserStatus::Death)
            return;

        if (!user->skillAbility.type70.triggered)
            return;

        if (!user->skillAbility.type70.skillId || !user->skillAbility.type70.skillLv)
            return;

        auto now = GetTickCount();
        if (now < user->skillAbility.type70.keepTick)
            return;

        auto skillInfo = CGameData::GetSkillInfo(user->skillAbility.type70.skillId, user->skillAbility.type70.skillLv);
        if (!skillInfo)
            return;

        CUser::RemApplySkillBuff(user, skillInfo);
        user->skillAbility.type70.keepTick = now + (skillInfo->keepTime * 1000);
        CUser::AddApplySkillBuff(user, skillInfo);
    }

    void ability_70_remove(CUser* user)
    {
        if (!user->skillAbility.type70.triggered)
            return;

        if (!user->skillAbility.type70.skillId || !user->skillAbility.type70.skillLv)
            return;

        auto skillInfo = CGameData::GetSkillInfo(user->skillAbility.type70.skillId, user->skillAbility.type70.skillLv);
        if (!skillInfo)
            return;

        user->skillAbility.type70.triggered = false;
        user->skillAbility.type70.skillId = 0;
        user->skillAbility.type70.skillLv = 0;
        user->skillAbility.type70.keepTick = 0;

        SkillUseOutgoing outgoing{};
        outgoing.senderId = user->id;
        outgoing.targetId = user->id;
        outgoing.skillId = skillInfo->skillId;
        outgoing.skillLv = skillInfo->skillLv;
        outgoing.statusType = SkillUseStatusType::Stopped;

        SConnection::Send(&user->connection, &outgoing, sizeof(SkillUseOutgoing));
        CUser::RemApplySkillBuff(user, skillInfo);
    }

    void set_ability_hook(CUser* user, int typeEffect, SkillAbilityType abilityType, int abilityValue)
    {
        switch (abilityType)
        {
        // skillId: 398, 399, 400, 401
        case SkillAbilityType::DecreaseHpByPercentage:
        {
            if (abilityValue < 0)
                return;

            user->health -= (user->health * abilityValue) / 100;
            CUser::SendRecoverChange(user, user->health, user->stamina, user->mana);
            break;
        }
        // itemId: 101112, 101113
        // skillId: 432
        case SkillAbilityType::IncreaseQuestExpRate:
            user->skillAbility.type87QuestExpRate += abilityValue;
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
        cmp byte ptr[esi+0x7C],0x46
        jne original

        pushad

        push esi // skillInfo
        push ebp // sender
        call user_apply_skill::ability_70_handler
        add esp,0x8

        popad

        jmp u0x45CD11

        original:
        mov ecx,[edi+0xDC]
        jmp u0x45CCE9
    }
}

unsigned u0x493BCF = 0x493BCF;
unsigned u0x493C3F = 0x493C3F;
void __declspec(naked) naked_0x493BC6()
{
    __asm
    {
        cmp byte ptr[ebp+0x7C],0x46
        je _0x493C3F

        // original
        mov edx,[ebp+0x5C]
        imul edx,edx,0x3E8
        jmp u0x493BCF

        _0x493C3F:
        jmp u0x493C3F
    }
}

unsigned u0x495EF4 = 0x495EF4;
void __declspec(naked) naked_0x495EEE()
{
    __asm
    {
        pushad

        push esi
        call user_apply_skill::ability_70_check_apply
        add esp,0x4

        popad

        // original
        lea eax,[esi+0xA98]
        jmp u0x495EF4
    }
}

unsigned u0x498623 = 0x498623;
void __declspec(naked) naked_0x49861D()
{
    __asm
    {
        pushad

        push esi // user
        call user_apply_skill::ability_70_remove
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
        call user_apply_skill::ability_70_remove
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

        cmp byte ptr[esi+0x7C],0x46
        jne _0x4935B7

        pushad

        push ebp // user
        call user_apply_skill::ability_70_remove
        add esp,0x4

        popad

        _0x4935B7:
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
        call user_apply_skill::set_ability_hook
        add esp,0x10

        popad

        // original
        pop esi
        mov esp,ebp
        pop ebp
        retn 0x4
    }
}

void hook::user_apply_skill()
{
    // CUser::SkillAttackRange
    util::detour((void*)0x45CCE3, naked_0x45CCE3, 6);
    // CUser::AddApplySkill
    util::detour((void*)0x493BC6, naked_0x493BC6, 9);
    // CUser::ChkEndTimeSkill
    util::detour((void*)0x495EEE, naked_0x495EEE, 6);
    // CUser::ClearApplySkillByDeath
    util::detour((void*)0x49861D, naked_0x49861D, 6);
    // CUser::SkillClearAll
    util::detour((void*)0x49887C, naked_0x49887C, 6);
    // CUser::LearnSkill
    util::detour((void*)0x4935B2, naked_0x4935B2, 5);
    // CUser::SetSkillAbility (default case)
    util::detour((void*)0x4959A4, naked_0x4959A4, 7);
}
