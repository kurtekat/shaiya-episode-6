#pragma unmanaged
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

        auto recovery = user->abilityRecovery;
        recovery -= user->recovery;
        packet.recovery = recovery;

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

void hook::user_status()
{
    // CUser::SetAttack
    util::detour((void*)0x461005, naked_0x461005, 5);
}
