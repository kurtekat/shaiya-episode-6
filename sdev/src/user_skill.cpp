#include <util/util.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include "include/main.h"
#include "include/shaiya/CharmType.h"
#include "include/shaiya/CMap.h"
#include "include/shaiya/CSkill.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/SkillInfo.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

void send_0x511(CUser* user, int skillId, int skillLv, ToggleType toggleType)
{
    GameCharSkillUseOutgoing_EP6 outgoing{};
    outgoing.senderId = user->id;
    outgoing.targetId = user->id;
    outgoing.skillId = skillId;
    outgoing.skillLv = skillLv;
    outgoing.toggleType = toggleType;
    SConnection::Send(user, &outgoing, sizeof(GameCharSkillUseOutgoing_EP6));
}

void func_0x45CCE3_70(CUser* user, SkillInfo* skillInfo)
{
    user->ability70Triggered = !user->ability70Triggered;
    auto toggleType = user->ability70Triggered ? ToggleType::Triggered : ToggleType::Stopped;
    send_0x511(user, skillInfo->skillId, skillInfo->skillLv, toggleType);
}

void func_0x45CCE3_71(CUser* user, SkillInfo* skillInfo)
{
    user->ability71Triggered = !user->ability71Triggered;
    auto toggleType = user->ability71Triggered ? ToggleType::Triggered : ToggleType::Stopped;
    send_0x511(user, skillInfo->skillId, skillInfo->skillLv, toggleType);
}

void func_0x45CCE3_72(CUser* user, SkillInfo* skillInfo)
{
    user->ability72Triggered = !user->ability72Triggered;
    auto toggleType = user->ability72Triggered ? ToggleType::Triggered : ToggleType::Stopped;
    send_0x511(user, skillInfo->skillId, skillInfo->skillLv, toggleType);
}

int hook_0x45CCE3(CUser* user, SkillInfo* skillInfo)
{
    auto abilityType1 = skillInfo->abilities[0].type;
    switch (abilityType1)
    {
    case SkillAbilityType::SubHpPercentage:
    {
        func_0x45CCE3_70(user, skillInfo);
        return 1;
    }
    case SkillAbilityType::SubSpPercentage:
    {
        func_0x45CCE3_71(user, skillInfo);
        return 1;
    }
    case SkillAbilityType::SubMpPercentage:
    {
        func_0x45CCE3_72(user, skillInfo);
        return 1;
    }
    default:
        return 0;
    }
}

void func_0x496067_70(CUser* user, CSkill* skill, tick32_t time)
{
    if (!user->ability70Triggered)
    {
        skill->endTime = time;
        return;
    }

    if (time < skill->endTime)
        return;

    int needSP = skill->info->needSP;
    if (needSP > user->stamina)
    {
        user->ability70Triggered = false;
        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughSP);
        skill->endTime = time;
        return;
    }

    int needMP = skill->info->needMP;
    if (needMP > user->mana)
    {
        user->ability70Triggered = false;
        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughMP);
        skill->endTime = time;
        return;
    }

    CUser::SendUseSPMP(user, needSP, needMP);

    int percent = skill->info->abilities[0].value;
    int maxHP = user->maxHealth;
    int damage = (maxHP * percent) / 100;

    if (user->health < damage)
    {
        user->ability70Triggered = false;
        user->health = 1;

        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughHP);
        skill->endTime = time;
    }
    else
    {
        user->health -= damage;
        skill->endTime = time + (skill->info->keepTime * 1000);
    }

    CUser::SendRecoverChange(user, user->health, user->stamina, user->mana);
}

void func_0x496067_71(CUser* user, CSkill* skill, tick32_t time)
{
    if (!user->ability71Triggered)
    {
        skill->endTime = time;
        return;
    }

    if (time < skill->endTime)
        return;

    int needSP = skill->info->needSP;
    if (needSP > user->stamina)
    {
        user->ability71Triggered = false;
        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughSP);
        skill->endTime = time;
        return;
    }

    int needMP = skill->info->needMP;
    if (needMP > user->mana)
    {
        user->ability71Triggered = false;
        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughMP);
        skill->endTime = time;
        return;
    }

    CUser::SendUseSPMP(user, needSP, needMP);

    int percent = skill->info->abilities[0].value;
    int maxSP = user->maxStamina;
    int damage = (maxSP * percent) / 100;

    if (user->stamina < damage)
    {
        user->ability71Triggered = false;
        user->stamina = 0;

        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughSP);
        skill->endTime = time;
    }
    else
    {
        user->stamina -= damage;
        skill->endTime = time + (skill->info->keepTime * 1000);
    }

    CUser::SendRecoverChange(user, user->health, user->stamina, user->mana);
}

void func_0x496067_72(CUser* user, CSkill* skill, tick32_t time)
{
    if (!user->ability72Triggered)
    {
        skill->endTime = time;
        return;
    }

    if (time < skill->endTime)
        return;

    int needSP = skill->info->needSP;
    if (needSP > user->stamina)
    {
        user->ability72Triggered = false;
        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughSP);
        skill->endTime = time;
        return;
    }

    int needMP = skill->info->needMP;
    if (needMP > user->mana)
    {
        user->ability72Triggered = false;
        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughMP);
        skill->endTime = time;
        return;
    }

    CUser::SendUseSPMP(user, needSP, needMP);

    int percent = skill->info->abilities[0].value;
    int maxMP = user->maxMana;
    int damage = (maxMP * percent) / 100;

    if (user->mana < damage)
    {
        user->ability72Triggered = false;
        user->mana = 0;

        send_0x511(user, skill->skillId, skill->skillLv, ToggleType::NotEnoughMP);
        skill->endTime = time;
    }
    else
    {
        user->mana -= damage;
        skill->endTime = time + (skill->info->keepTime * 1000);
    }

    CUser::SendRecoverChange(user, user->health, user->stamina, user->mana);
}

void hook_0x496067(CUser* user, CSkill* skill, tick32_t time)
{
    auto abilityType1 = skill->info->abilities[0].type;
    switch (abilityType1)
    {
    case SkillAbilityType::SubHpPercentage:
        func_0x496067_70(user, skill, time);
        break;
    case SkillAbilityType::SubSpPercentage:
        func_0x496067_71(user, skill, time);
        break;
    case SkillAbilityType::SubMpPercentage:
        func_0x496067_72(user, skill, time);
        break;
    default:
        return;
    }
}

void hook_0x498500(CUser* user, SkillInfo* skillInfo)
{
    auto abilityType1 = skillInfo->abilities[0].type;
    switch (abilityType1)
    {
    case SkillAbilityType::SubHpPercentage:
        user->ability70Triggered = false;
        break;
    case SkillAbilityType::SubSpPercentage:
        user->ability71Triggered = false;
        break;
    case SkillAbilityType::SubMpPercentage:
        user->ability72Triggered = false;
        break;
    default:
        return;
    }

    send_0x511(user, skillInfo->skillId, skillInfo->skillLv, ToggleType::Stopped);
}

void hook_0x498806(CUser* user, SkillInfo* skillInfo)
{
    auto abilityType1 = skillInfo->abilities[0].type;
    switch (abilityType1)
    {
    case SkillAbilityType::SubHpPercentage:
        user->ability70Triggered = false;
        break;
    case SkillAbilityType::SubSpPercentage:
        user->ability71Triggered = false;
        break;
    case SkillAbilityType::SubMpPercentage:
        user->ability72Triggered = false;
        break;
    default:
        return;
    }

    send_0x511(user, skillInfo->skillId, skillInfo->skillLv, ToggleType::Stopped);
}

void hook_0x4935B2(CUser* user, SkillInfo* skillInfo)
{
    auto abilityType1 = skillInfo->abilities[0].type;
    switch (abilityType1)
    {
    case SkillAbilityType::SubHpPercentage:
        user->ability70Triggered = false;
        break;
    case SkillAbilityType::SubSpPercentage:
        user->ability71Triggered = false;
        break;
    case SkillAbilityType::SubMpPercentage:
        user->ability72Triggered = false;
        break;
    default:
        return;
    }

    send_0x511(user, skillInfo->skillId, skillInfo->skillLv, ToggleType::Stopped);
}

/// <summary>
/// Extends skill ability support. The abilityValue will be negative when a skill is removed.
/// </summary>
void hook_0x4959A4(CUser* user, int typeEffect, SkillAbilityType abilityType, int abilityValue)
{
    switch (abilityType)
    {
    // See SkillID 432
    case SkillAbilityType::MultiplyQuestExp:
        user->multiplyQuestExpRate += abilityValue;
        break;
    default:
        break;
    }
}

/// <summary>
/// Adds support for skill ability 87.
/// </summary>
int hook_0x465087(CUser* user, int exp, bool isQuest)
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
    case CharmType::BlueDragon:
    case CharmType::WhiteTiger:
    case CharmType::RedPhoenix:
        multiplier += 0.2;
        break;
    default:
        break;
    }

    // expupmap (PSMServer_Mgr)

    auto zone = user->zone;
    if (zone)
    {
        auto map = zone->map;
        if (map)
        {
            multiplier *= map->expMultiplier;
        }
    }

    // expupcamp (PSMServer_Mgr)

    switch (user->country)
    {
    case Country::Light:
        multiplier *= *reinterpret_cast<double*>(0x582768);
        break;
    case Country::Fury:
        multiplier *= *reinterpret_cast<double*>(0x582770);
        break;
    default:
        break;
    }

    auto bonus = multiplier * exp;
    return static_cast<int>(bonus);
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
        call hook_0x45CCE3
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
void __declspec(naked) naked_0x496067()
{
    __asm
    {
        pushad

        mov edx,[ebp+0x08]

        push edx // time
        push ebx // skill
        push esi // user
        call hook_0x496067
        add esp,0xC

        popad

        // original
        mov edx,[ebp+0x08]
        cmp edx,[ebx+0x20]
        jmp u0x49606D
    }
}

unsigned u0x498506 = 0x498506;
void __declspec(naked) naked_0x498500()
{
    // TypeDetail case 82
    __asm
    {
        pushad

        push edi // skillInfo
        push esi // user
        call hook_0x498500
        add esp,0x8

        popad

        // original
        movzx eax,word ptr[edi+0x7E]
        neg eax
        jmp u0x498506
    }
}

unsigned u0x49880C = 0x49880C;
void __declspec(naked) naked_0x498806()
{
    // TypeDetail case 82
    __asm
    {
        pushad

        push edi // skillInfo
        push esi // user
        call hook_0x498806
        add esp,0x8

        popad

        // original
        movzx eax,word ptr[edi+0x7E]
        neg eax
        jmp u0x49880C
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
        call hook_0x4935B2
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
        call hook_0x4959A4
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
        mov ecx,[esp+0x40]

        push eax // isQuest
        push ecx // exp
        push esi // user
        call hook_0x465087
        add esp,0xC

        mov [esp+0x40],eax

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
    util::detour((void*)0x498500, naked_0x498500, 6);
    // CUser::SkillClearAll
    util::detour((void*)0x498806, naked_0x498806, 6);
    // CUser::LearnSkill
    util::detour((void*)0x4935B2, naked_0x4935B2, 5);
    // CUser::SetSkillAbility (default case)
    util::detour((void*)0x4959A4, naked_0x4959A4, 7);
    // CUser::AddExpFromUser
    util::detour((void*)0x465087, naked_0x465087, 5);
}
