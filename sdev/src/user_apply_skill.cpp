#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/shaiya/packets/0500.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CSkill.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/CZone.h>
#include <include/shaiya/include/SConnection.h>
#include <util/include/util.h>
using namespace shaiya;

namespace user_apply_skill
{
    void frenzy_handler(CUser* user, CGameData::SkillInfo* skillInfo)
    {
        SkillUseOutgoing packet{};
        packet.senderId = user->id;
        packet.targetId = user->id;
        packet.skillId = skillInfo->skillId;
        packet.skillLv = skillInfo->skillLv;

        if (!user->frenzy.triggered)
        {
#ifdef SHAIYA_EP6_COMMON
            packet.frenzyState = SkillUseFrenzyState::Triggered;
#endif

            user->frenzy.triggered = true;
            user->frenzy.skillId = packet.skillId;
            user->frenzy.skillLv = packet.skillLv;
            user->frenzy.keepTime = GetTickCount() + (skillInfo->keepTime * 1000);

            SConnection::Send(&user->connection, &packet, sizeof(SkillUseOutgoing));
            CUser::AddApplySkillBuff(user, skillInfo);

            auto percentage = (user->health * skillInfo->ability[0].value) / 100;
            user->health -= percentage;
            CUser::SendRecoverSet(user, user->health, user->stamina, user->mana);
        }
        else
        {
#ifdef SHAIYA_EP6_COMMON
            packet.frenzyState = SkillUseFrenzyState::Stopped;
#endif

            user->frenzy.triggered = false;
            user->frenzy.skillId = 0;
            user->frenzy.skillLv = 0;
            user->frenzy.keepTime = 0;

            SConnection::Send(&user->connection, &packet, sizeof(SkillUseOutgoing));
            CUser::RemApplySkillBuff(user, skillInfo);
        }
    }

    void frenzy_update(CUser* user)
    {
        if (!user)
            return;

        auto now = GetTickCount();
        if (!user->frenzy.triggered || now < user->frenzy.keepTime)
            return;

        auto skillInfo = CGameData::GetSkillInfo(user->frenzy.skillId, user->frenzy.skillLv);
        if (!skillInfo)
            return;

        auto percentage = (user->health * skillInfo->ability[0].value) / 100;
        user->health -= percentage;
        CUser::SendRecoverSet(user, user->health, user->stamina, user->mana);

        user->frenzy.keepTime = now + (skillInfo->keepTime * 1000);
    }

    void frenzy_remove(CUser* user)
    {
        if (!user->frenzy.triggered)
            return;

        auto skillInfo = CGameData::GetSkillInfo(user->frenzy.skillId, user->frenzy.skillLv);
        if (!skillInfo)
            return;

        user->frenzy.triggered = false;
        user->frenzy.skillId = 0;
        user->frenzy.skillLv = 0;
        user->frenzy.keepTime = 0;

        CUser::RemApplySkillBuff(user, skillInfo);
    }

    void send_view(CUser* sender, CUser* target, CGameData::SkillInfo* skillInfo, Packet buffer)
    {
        if (skillInfo->ability[0].type == CGameData::SkillAbilityType::Frenzied)
            return frenzy_handler(sender, skillInfo);

        SkillUseOutgoing packet{};
        packet.targetType = util::deserialize<std::uint8_t>(buffer, 2, 20);
        packet.senderId = sender->id;
        packet.targetId = target->id;
        packet.skillId = util::deserialize<std::uint16_t>(buffer, 11, 20);
        packet.skillLv = util::deserialize<std::uint8_t>(buffer, 13, 20);
        packet.health = util::deserialize<std::uint16_t>(buffer, 14, 20);
        packet.stamina = util::deserialize<std::uint16_t>(buffer, 16, 20);
        packet.mana = util::deserialize<std::uint16_t>(buffer, 18, 20);

        if (!sender->zone)
            return;

        CZone::PSendView(sender->zone, &packet, sizeof(SkillUseOutgoing), &sender->pos, 60, sender->id, target->id, 5);
    }
}

unsigned u0x45CD11 = 0x45CD11;
void __declspec(naked) naked_0x45CCE3()
{
    __asm
    {
        pushad

        lea eax,[esp+0x3C]

        push eax // packet
        push esi // skillInfo
        push edi // target
        push ebp // sender
        call user_apply_skill::send_view
        add esp,0x10

        popad

        jmp u0x45CD11
    }
}

unsigned u0x493BCF = 0x493BCF;
unsigned u0x493C3F = 0x493C3F;
void __declspec(naked) naked_0x493BC6()
{
    __asm
    {
        // abilityType1
        movzx edx,byte ptr[ebp+0x7C]
        cmp edx,0x46
        je _0x493C3F

        // original
        mov edx,[ebp+0x5C]
        imul edx,edx,0x3E8
        jmp u0x493BCF

        _0x493C3F:
        jmp u0x493C3F
    }
}

unsigned u0x49DB20 = 0x49DB20;
unsigned u0x428ADA = 0x428ADA;
void __declspec(naked) naked_0x428AD5()
{
    __asm
    {
        // original
        call u0x49DB20

        pushad

        lea edx,[esi-0xD0]
        push edx // user
        call user_apply_skill::frenzy_update
        add esp,0x4

        popad

        jmp u0x428ADA
    }
}

unsigned u0x498623 = 0x498623;
void __declspec(naked) naked_0x49861D()
{
    __asm
    {
        pushad

        push esi // user
        call user_apply_skill::frenzy_remove
        add esp,0x4

        popad

        // original
        mov eax,[esi+0x1C4]
        jmp u0x498623
    }
}

void hook::user_apply_skill()
{
    // CUser::SkillAttackRange
    util::detour((void*)0x45CCE3, naked_0x45CCE3, 6);
    // CUser::AddApplySkill
    util::detour((void*)0x493BC6, naked_0x493BC6, 9);
    // CZone::UpdateApplySkill
    util::detour((void*)0x428AD5, naked_0x428AD5, 5);
    // CUser::ClearApplySkillByDeath
    util::detour((void*)0x49861D, naked_0x49861D, 6);
}
