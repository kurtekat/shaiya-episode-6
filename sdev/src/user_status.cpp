#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/ItemInfo.h>
#include <include/shaiya/include/Synergy.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include <util/include/util.h>
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
}
