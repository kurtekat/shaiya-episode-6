#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0526.h>
#include <shaiya/include/CGameData.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace user_status
{
    void send_status(CUser* user)
    {
        UserStatus packet{};
        packet.opcode = 0x526;

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

        auto attack_power = user->minMeleeAtkPower;

        if (user->inventory[0][EquipmentSlot::Weapon])
        {
            auto real_type = user->inventory[0][EquipmentSlot::Weapon]->itemInfo->realType;

            switch (real_type)
            {
            case CGameData::ItemRealType::Javelin:
            case CGameData::ItemRealType::Bow:
            case CGameData::ItemRealType::Crossbow:
                attack_power = user->minRangeAtkPower;
                break;
            default:
                break;
            }
        }

        packet.minAttackPower = attack_power;
        attack_power += user->maxAddAtkPower;
        packet.maxAttackPower = attack_power;

        auto magic_power = user->minMagicPower;
        packet.minMagicPower = magic_power;
        magic_power += user->maxAddAtkPower;
        packet.maxMagicPower = magic_power;

        packet.defense = user->meleeDefense;
        packet.resistance = user->magicResistance;

        SConnection::Send(user, &packet, sizeof(packet));
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
        call user_status::send_status
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

    // remove subractions

    std::array<std::uint8_t, 2> a00{ 0x90, 0x90 };
    // CUser::SendRecoverAdd
    util::write_memory((void*)0x490E35, &a00, 2);
    util::write_memory((void*)0x490E41, &a00, 2);
    util::write_memory((void*)0x490E5D, &a00, 2);
    // CUser::SendRecoverAddSet
    util::write_memory((void*)0x490F52, &a00, 2);
    util::write_memory((void*)0x490F5E, &a00, 2);
    util::write_memory((void*)0x490F7A, &a00, 2);
}
