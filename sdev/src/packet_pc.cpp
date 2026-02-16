#include <util/util.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/network/game/incoming/0500.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include "include/main.h"
#include "include/operator.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

namespace packet_pc
{
    /// <summary>
    /// Handles incoming 0x55A packets.
    /// </summary>
    void handler_0x55A(CUser* user, GameTownMoveScrollIncoming* incoming)
    {
        if (user->status == UserStatus::Death)
            return;

        if (user->debuffTypeDetail)
            return;

        if (user->logoutTime)
            return;

        if (!incoming->bag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag, incoming->slot))
            return;

        if (incoming->gateIndex > 2)
            return;

        user->savePosUseIndex = incoming->gateIndex;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);
        CUser::ItemUse(user, incoming->bag, incoming->slot, user->id, 0);
    }

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

        auto& weapon = user->inventory[0][5];
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
        SConnection::Send(user, &outgoing, sizeof(GameUserStatusOutgoing));
    }
}

unsigned u0x4784DB = 0x4784DB;
unsigned u0x479155 = 0x479155;
void __declspec(naked) naked_0x4784D6()
{
    __asm
    {
        add eax,-0x501
        cmp eax,0x59
        je case_0x55A
        jmp u0x4784DB

        case_0x55A:
        pushad

        push ebp // packet
        push ecx // user
        call packet_pc::handler_0x55A
        add esp,0x8

        popad

        jmp u0x479155
    }
}

void __declspec(naked) naked_0x461005()
{
    __asm
    {
        pushad

        push esi // user
        call packet_pc::send_0x526
        add esp,0x4

        popad

        // original
        pop ebx
        add esp,0x8
        retn
    }
}

double g_itemRepairBuyDivisor = 15.0;
unsigned u0x471C29 = 0x471C29;
void __declspec(naked) naked_0x471C23()
{
    __asm
    {
        fld qword ptr[g_itemRepairBuyDivisor]
        jmp u0x471C29
    }
}

unsigned u0x472030 = 0x472030;
void __declspec(naked) naked_0x47202A()
{
    __asm
    {
        fdiv qword ptr[g_itemRepairBuyDivisor]
        jmp u0x472030
    }
}

void hook::packet_pc()
{
    // CUser::PacketPC
    util::detour((void*)0x4784D6, naked_0x4784D6, 5);
    // CUser::SetAttack
    util::detour((void*)0x461005, naked_0x461005, 5);
    // CUser::ItemRepair
    util::detour((void*)0x471C23, naked_0x471C23, 6);
    util::detour((void*)0x47202A, naked_0x47202A, 6);

    // CUser::SendRecoverAdd
    util::write_memory((void*)0x490E35, 0x90, 2);
    util::write_memory((void*)0x490E41, 0x90, 2);
    util::write_memory((void*)0x490E5D, 0x90, 2);

    // CUser::SendRecoverAddSet
    util::write_memory((void*)0x490F52, 0x90, 2);
    util::write_memory((void*)0x490F5E, 0x90, 2);
    util::write_memory((void*)0x490F7A, 0x90, 2);
}
