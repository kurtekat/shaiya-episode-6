#include <array>
#include <shaiya/include/common/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/Synergy.h"
#include "include/shaiya/include/network/game/outgoing/0500.h"
using namespace shaiya;

namespace user_status
{
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

        auto& weapon = user->inventory[0][EquipmentSlot::Weapon];
        if (weapon)
        {
            switch (weapon->itemInfo->realType)
            {
            case ItemRealType::Javelin:
            case ItemRealType::Bow:
            case ItemRealType::Crossbow:
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

        SConnection::Send(&user->connection, &outgoing, sizeof(UserStatusOutgoing));
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

unsigned u0x461646 = 0x461646;
void __declspec(naked) naked_0x461640()
{
    __asm
    {
        pushad

        push 0x0 // remove flag
        push eax // item
        push edi // user
        call Synergy::applySynergies
        add esp,0xC

        popad

        sub esp,0x1C
        push ebx
        mov ebx,eax
        jmp u0x461646
    }
}

unsigned u0x461D16 = 0x461D16;
void __declspec(naked) naked_0x461D10()
{
    __asm
    {
        pushad

        push 0x1 // remove flag
        push ecx // item
        push edx // user
        call Synergy::applySynergies
        add esp,0xC

        popad

        push ebp
        mov ebp,esp
        and esp,-0x8
        jmp u0x461D16
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

        push edi
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

        push esi
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
    util::detour((void*)0x461640, naked_0x461640, 6);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D10, naked_0x461D10, 6);
    // CUser::StatResetStatus
    util::detour((void*)0x48F9BE, naked_0x48F9BE, 7);
    // CUser::StatResetSkill
    util::detour((void*)0x48FCD3, naked_0x48FCD3, 7);

#ifdef SHAIYA_EP6_4_PT
    // CUser::SendRecoverAdd
    util::write_memory((void*)0x490E35, 0x90, 2);
    util::write_memory((void*)0x490E41, 0x90, 2);
    util::write_memory((void*)0x490E5D, 0x90, 2);

    // CUser::SendRecoverAddSet
    util::write_memory((void*)0x490F52, 0x90, 2);
    util::write_memory((void*)0x490F5E, 0x90, 2);
    util::write_memory((void*)0x490F7A, 0x90, 2);
#endif
}
