#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0500.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CSkill.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/CZone.h>
#include <include/shaiya/include/SConnection.h>
using namespace shaiya;

namespace user_apply_skill
{
    void send_frenzy_state(CUser* user, CGameData::SkillInfo* skillInfo)
    {
        SkillUseOutgoing packet{};
        packet.senderId = user->id;
        packet.targetId = user->id;
        packet.skillId = skillInfo->skillId;
        packet.skillLv = skillInfo->skillLv;

        if (!user->activableSkill.triggered)
        {
            packet.targetType = static_cast<std::uint8_t>(skillInfo->targetType);
            #ifdef SHAIYA_EP6_0511
            packet.state = SkillUseState::Triggered;
            #endif

            user->activableSkill.triggered = true;
            user->activableSkill.id = packet.skillId;
            user->activableSkill.level = packet.skillLv;
            user->activableSkill.keepTime = GetTickCount() + (skillInfo->keepTime * 1000);

            SConnection::Send(&user->connection, &packet, sizeof(SkillUseOutgoing));
            CUser::AddApplySkillBuff(user, skillInfo);

            auto percentage = (user->health * skillInfo->ability[0].value) / 100;
            user->health -= percentage;
            CUser::SendRecoverSet(user, user->health, user->stamina, user->mana);
            return;
        }
        else
        {
            packet.targetType = static_cast<std::uint8_t>(skillInfo->targetType);
            #ifdef SHAIYA_EP6_0511
            packet.state = SkillUseState::Stopped;
            #endif

            user->activableSkill.triggered = false;
            user->activableSkill.id = 0;
            user->activableSkill.level = 0;
            user->activableSkill.keepTime = 0;

            SConnection::Send(&user->connection, &packet, sizeof(SkillUseOutgoing));
            CUser::RemApplySkillBuff(user, skillInfo);
            return;
        }
    }

    void send_keep_damage(CUser* user)
    {
        if (!user)
            return;

        auto now = GetTickCount();
        if (!user->activableSkill.triggered || now < user->activableSkill.keepTime)
            return;

        auto skillInfo = CGameData::GetSkillInfo(user->activableSkill.id, user->activableSkill.level);
        if (!skillInfo)
            return;

        auto percentage = (user->health * skillInfo->ability[0].value) / 100;
        user->health -= percentage;
        CUser::SendRecoverSet(user, user->health, user->stamina, user->mana);

        user->activableSkill.keepTime = now + (skillInfo->keepTime * 1000);
    }

    void maybe_send_state(CUser* sender, CUser* target, CGameData::SkillInfo* skillInfo, Packet buffer)
    {
        SkillUseOutgoing packet{};
        packet.targetType = util::read_bytes<std::uint8_t>(buffer, 2);
        packet.senderId = sender->id;
        packet.targetId = target->id;
        packet.skillId = util::read_bytes<std::uint16_t>(buffer, 11);
        packet.skillLv = util::read_bytes<std::uint8_t>(buffer, 13);
        packet.health = util::read_bytes<std::uint16_t>(buffer, 14);
        packet.stamina = util::read_bytes<std::uint16_t>(buffer, 16);
        packet.mana = util::read_bytes<std::uint16_t>(buffer, 18);

        switch (packet.skillId)
        {
        case CGameData::SkillId::FrenziedForce:
        case CGameData::SkillId::FrenziedFocus:
        case CGameData::SkillId::FrenziedFinesse:
        case CGameData::SkillId::FrenziedFortune:
        {
            send_frenzy_state(sender, skillInfo);
            return;
        }
        default:
            break;
        }

        if (!sender->zone)
            return;

        CZone::PSendView(sender->zone, &packet, sizeof(SkillUseOutgoing), &sender->pos, 60, sender->id, target->id, 5);
    }

    bool is_activable(CSkill* skill)
    {
        switch (skill->skillId)
        {
        case CGameData::SkillId::FrenziedForce:
        case CGameData::SkillId::FrenziedFocus:
        case CGameData::SkillId::FrenziedFinesse:
        case CGameData::SkillId::FrenziedFortune:
            return true;
        default:
            break;
        }

        return false;
    }

    void remove_activable(CUser* user)
    {
        if (user->activableSkill.triggered)
        {
            auto skillInfo = CGameData::GetSkillInfo(user->activableSkill.id, user->activableSkill.level);
            if (!skillInfo)
                return;

            user->activableSkill.triggered = false;
            user->activableSkill.id = 0;
            user->activableSkill.level = 0;
            user->activableSkill.keepTime = 0;

            CUser::RemApplySkillBuff(user, skillInfo);
            return;
        }
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
        push ebp // user
        call user_apply_skill::maybe_send_state
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
        pushad

        push ebx // skill
        call user_apply_skill::is_activable
        add esp,0x4
        test al,al

        popad

        jne _0x493C3F

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
        call user_apply_skill::send_keep_damage
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
        call user_apply_skill::remove_activable
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
