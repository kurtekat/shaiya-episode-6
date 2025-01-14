#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/Synergy.h"
#include "include/shaiya/include/network/game/outgoing/0500.h"
using namespace shaiya;

namespace user_status
{
    /// <summary>
    /// Sends packet 0x526 to the user.
    /// </summary>
    /// <param name="user"></param>
    void send(CUser* user)
    {
        UserStatusOutgoing outgoing{};

        auto strength = user->abilityStrength;
        strength -= user->strength;
        outgoing.strength = strength;

        auto reaction = user->abilityReaction;
        reaction -= user->reaction;
        outgoing.reaction = reaction;

        auto intelligence = user->abilityIntelligence;
        intelligence -= user->intelligence;
        outgoing.intelligence = intelligence;

        auto wisdom = user->abilityWisdom;
        wisdom -= user->wisdom;
        outgoing.wisdom = wisdom;

        auto dexterity = user->abilityDexterity;
        dexterity -= user->dexterity;
        outgoing.dexterity = dexterity;

        auto luck = user->abilityLuck;
        luck -= user->luck;
        outgoing.luck = luck;

        auto attackPower = user->minAttackPower;

        auto& weapon = user->inventory[0][int(EquipmentSlot::Weapon)];
        if (weapon)
        {
            switch (weapon->itemInfo->realType)
            {
            case RealType::Javelin:
            case RealType::Bow:
            case RealType::Crossbow:
                attackPower = user->minRangedAttackPower;
                break;
            default:
                break;
            }
        }

        outgoing.minAttackPower = attackPower;
        attackPower += user->maxAddAttackPower;
        outgoing.maxAttackPower = attackPower;

        auto magicPower = user->minMagicPower;
        outgoing.minMagicPower = magicPower;
        magicPower += user->maxAddAttackPower;
        outgoing.maxMagicPower = magicPower;

        outgoing.defense = user->defense;
        outgoing.resistance = user->magicResistance;
        NetworkHelper::Send(user, &outgoing, sizeof(UserStatusOutgoing));
    }
}

void __declspec(naked) naked_0x461005()
{
    __asm
    {
        pushad

        push esi // user
        call user_status::send
        add esp,0x4

        popad

        // original
        pop ebx
        add esp,0x8
        retn
    }
}

unsigned u0x46166E = 0x46166E;
void __declspec(naked) naked_0x461667()
{
    __asm
    {
        // original
        mov [edi+ebp+0x199],al

        pushad

        push edi // user
        call Synergy::equipmentAdd
        add esp,0x4

        popad

        jmp u0x46166E
    }
}

unsigned u0x461D43 = 0x461D43;
void __declspec(naked) naked_0x461D3C()
{
    __asm
    {
        // original
        mov ebx,ecx
        mov ecx,[ebp+0x8]
        mov edi,edx

        pushad

        push ecx // slot
        push edi // user
        call Synergy::equipmentRemove
        add esp,0x8

        popad

        jmp u0x461D43
    }
}

// CUser::InitEquipment
unsigned u0x461010 = 0x461010;
unsigned u0x48F9C5 = 0x48F9C5;
void __declspec(naked) naked_0x48F9BE()
{
    __asm
    {
        pushad

        push edi // user
        call Synergy::removeSynergies
        add esp,0x4

        popad

        // original
        mov eax,edi
        call u0x461010

        jmp u0x48F9C5
    }
}

unsigned u0x48FCDA = 0x48FCDA;
void __declspec(naked) naked_0x48FCD3()
{
    __asm
    {
        pushad

        push esi // user
        call Synergy::removeSynergies
        add esp,0x4

        popad

        // original
        mov eax,esi
        call u0x461010

        jmp u0x48FCDA
    }
}

void hook::user_status()
{
    // CUser::SetAttack
    util::detour((void*)0x461005, naked_0x461005, 5);
    // CUser::ItemEquipmentAdd
    util::detour((void*)0x461667, naked_0x461667, 7);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D3C, naked_0x461D3C, 7);
    // CUser::StatResetStatus
    util::detour((void*)0x48F9BE, naked_0x48F9BE, 7);
    // CUser::StatResetSkill
    util::detour((void*)0x48FCD3, naked_0x48FCD3, 7);

    // CUser::SendRecoverAdd
    util::write_memory((void*)0x490E35, 0x90, 2);
    util::write_memory((void*)0x490E41, 0x90, 2);
    util::write_memory((void*)0x490E5D, 0x90, 2);

    // CUser::SendRecoverAddSet
    util::write_memory((void*)0x490F52, 0x90, 2);
    util::write_memory((void*)0x490F5E, 0x90, 2);
    util::write_memory((void*)0x490F7A, 0x90, 2);
}
