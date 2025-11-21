#include <util/util.h>
#include <shaiya/include/common/ItemSlot.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NetworkHelper.h"
#include "include/shaiya/Synergy.h"
using namespace shaiya;

namespace user_status
{
    /// <summary>
    /// Sends packet 0x526 to the user.
    /// </summary>
    void send_0x526(CUser* user)
    {
        GameUserStatusOutgoing outgoing{};

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

        auto attackPower = user->attack.power;

        auto& weapon = user->inventory[0][ItemSlot::Weapon];
        if (weapon)
        {
            switch (weapon->info->realType)
            {
            case RealType::Javelin:
            case RealType::Bow:
            case RealType::Crossbow:
                attackPower = user->attackRanged.power;
                break;
            default:
                break;
            }
        }

        outgoing.minAttackPower = attackPower;
        attackPower += user->itemAttackPowerAdd;
        outgoing.maxAttackPower = attackPower;

        auto magicPower = user->attackMagic.power;
        outgoing.minMagicPower = magicPower;
        magicPower += user->itemAttackPowerAdd;
        outgoing.maxMagicPower = magicPower;

        outgoing.defense = user->attack.defense;
        outgoing.resistance = user->attackMagic.defense;
        NetworkHelper::Send(user, &outgoing, sizeof(GameUserStatusOutgoing));
    }
}

void __declspec(naked) naked_0x461005()
{
    __asm
    {
        pushad

        push esi // user
        call user_status::send_0x526
        add esp,0x4

        popad

        // original
        pop ebx
        add esp,0x8
        retn
    }
}

unsigned u0x461675 = 0x461675;
void __declspec(naked) naked_0x46166E()
{
    __asm
    {
        pushad

        push edi // user
        call Synergy::equipmentAdd
        add esp,0x4

        popad

        // original
        cmp byte ptr [edi+0x5855],0x0
        jmp u0x461675
    }
}

unsigned u0x461D4A = 0x461D4A;
void __declspec(naked) naked_0x461D43()
{
    __asm
    {
        pushad

        push ecx // slot
        push edi // user
        call Synergy::equipmentRemove
        add esp,0x8

        popad

        // original
        cmp byte ptr [edi+0x5855],0x0
        jmp u0x461D4A
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
    util::detour((void*)0x46166E, naked_0x46166E, 7);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D43, naked_0x461D43, 7);
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
