#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0526.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/Synergy.h>
using namespace shaiya;

namespace user_status
{
    void send(CUser* user)
    {
        UserStatusOutgoing packet{};

        auto strength = user->abilityStrength;
        strength -= user->strength;
        packet.strength = strength;

        auto reaction = user->abilityReaction;
        reaction -= user->reaction;
        packet.reaction = reaction;

        auto intelligence = user->abilityIntelligence;
        intelligence -= user->intelligence;
        packet.intelligence = intelligence;

        auto wisdom = user->abilityWisdom;
        wisdom -= user->wisdom;
        packet.wisdom = wisdom;

        auto dexterity = user->abilityDexterity;
        dexterity -= user->dexterity;
        packet.dexterity = dexterity;

        auto luck = user->abilityLuck;
        luck -= user->luck;
        packet.luck = luck;

        auto attackPower = user->minAttackPower;

        auto& weapon = user->inventory[0][EquipmentSlot::Weapon];
        if (weapon)
        {
            switch (weapon->itemInfo->realType)
            {
            case CGameData::ItemRealType::Javelin:
            case CGameData::ItemRealType::Bow:
            case CGameData::ItemRealType::Crossbow:
                attackPower = user->minRangedAttackPower;
                break;
            default:
                break;
            }
        }

        packet.minAttackPower = attackPower;
        attackPower += user->maxAddAttackPower;
        packet.maxAttackPower = attackPower;

        auto magicPower = user->minMagicPower;
        packet.minMagicPower = magicPower;
        magicPower += user->maxAddAttackPower;
        packet.maxMagicPower = magicPower;

        packet.defense = user->defense;
        packet.resistance = user->magicResistance;

        SConnection::Send(&user->connection, &packet, sizeof(UserStatusOutgoing));
    }

    void send_recover_set(CUser* user)
    {
        CUser::SendRecoverSet(user, user->health, user->stamina, user->mana);
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

unsigned u0x427CF0 = 0x427CF0;
unsigned u0x490E8E = 0x490E8E;
void __declspec(naked) naked_0x490E89()
{
    __asm
    {
        // original
        call u0x427CF0

        pushad

        push esi // user
        call user_status::send_recover_set
        add esp,0x4

        popad

        jmp u0x490E8E
    }
}

unsigned u0x490FAB = 0x490FAB;
void __declspec(naked) naked_0x490FA6()
{
    __asm
    {
        // original
        call u0x427CF0

        pushad

        push edi // user
        call user_status::send_recover_set
        add esp,0x4

        popad

        jmp u0x490FAB
    }
}

unsigned u0x4910D4 = 0x4910D4;
void __declspec(naked) naked_0x4910CF()
{
    __asm
    {
        // original
        call u0x427CF0

        pushad

        push esi // user
        call user_status::send_recover_set
        add esp,0x4

        popad

        jmp u0x4910D4
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
    // CUser::SendRecoverAdd
    util::detour((void*)0x490E89, naked_0x490E89, 5);
    // CUser::SendRecoverAddSet
    util::detour((void*)0x490FA6, naked_0x490FA6, 5);
    // CUser::SendRecoverChange
    util::detour((void*)0x4910CF, naked_0x4910CF, 5);

    #ifdef WITH_SET_ITEM
    // CUser::StatResetStatus
    util::detour((void*)0x48F9BE, naked_0x48F9BE, 7);
    // CUser::StatResetSkill
    util::detour((void*)0x48FCD3, naked_0x48FCD3, 7);
    #endif
}
