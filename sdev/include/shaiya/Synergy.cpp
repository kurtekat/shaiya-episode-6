#include <algorithm>
#include <map>
#include <vector>
#include <extensions/include/functional.hpp>
#include "CItem.h"
#include "CUser.h"
#include "ItemInfo.h"
#include "ItemPredicate.h"
#include "Synergy.h"
using namespace shaiya;

void Synergy::subSynergies(CUser* user, const std::vector<ItemSetSynergy>& synergies)
{
    auto maxHealth = user->maxHealth;
    auto maxMana = user->maxHealth;
    auto maxStamina = user->maxHealth;

    for (const auto& synergy : synergies)
    {
        auto strength = synergy.effects[0];
        auto dexterity = synergy.effects[1];
        auto reaction = synergy.effects[2];
        auto intelligence = synergy.effects[3];
        auto wisdom = synergy.effects[4];
        auto luck = synergy.effects[5];
        auto health = synergy.effects[6];
        auto mana = synergy.effects[7];
        auto stamina = synergy.effects[8];
        auto attackPower = synergy.effects[9];
        auto rangedAttackPower = synergy.effects[10];
        auto magicPower = synergy.effects[11];
        auto defense = synergy.effects[12];
        auto rangedDefense = synergy.effects[13];
        auto magicDefense = synergy.effects[14];

        user->abilityStrength -= strength;
        user->abilityDexterity -= dexterity;
        user->abilityReaction -= reaction;
        user->abilityIntelligence -= intelligence;
        user->abilityWisdom -= wisdom;
        user->abilityLuck -= luck;
        user->maxHealth -= health;
        user->maxMana -= mana;
        user->maxStamina -= stamina;
        user->attackAdd.power -= attackPower;
        user->attackAddRanged.power -= rangedAttackPower;
        user->attackAddMagic.power -= magicPower;
        user->attack.defense -= defense;
        user->attackRanged.defense -= rangedDefense;
        user->attackMagic.defense -= magicDefense;

        if (reaction)
            user->maxHealth -= reaction * 5;

        if (wisdom)
            user->maxMana -= wisdom * 5;

        if (dexterity)
            user->maxStamina -= dexterity * 5;
    }

    if (!user->initStatusFlag)
    {
        if (maxHealth != user->maxHealth)
            CUser::SendMaxHP(user);

        if (maxMana != user->maxMana)
            CUser::SendMaxMP(user);

        if (maxStamina != user->maxStamina)
            CUser::SendMaxSP(user);
    }
}

void Synergy::addSynergies(CUser* user, const std::vector<ItemSetSynergy>& synergies)
{
    auto maxHealth = user->maxHealth;
    auto maxMana = user->maxHealth;
    auto maxStamina = user->maxHealth;

    for (const auto& synergy : synergies)
    {
        auto strength = synergy.effects[0];
        auto dexterity = synergy.effects[1];
        auto reaction = synergy.effects[2];
        auto intelligence = synergy.effects[3];
        auto wisdom = synergy.effects[4];
        auto luck = synergy.effects[5];
        auto health = synergy.effects[6];
        auto mana = synergy.effects[7];
        auto stamina = synergy.effects[8];
        auto attackPower = synergy.effects[9];
        auto rangedAttackPower = synergy.effects[10];
        auto magicPower = synergy.effects[11];
        auto defense = synergy.effects[12];
        auto rangedDefense = synergy.effects[13];
        auto magicDefense = synergy.effects[14];

        user->abilityStrength += strength;
        user->abilityDexterity += dexterity;
        user->abilityReaction += reaction;
        user->abilityIntelligence += intelligence;
        user->abilityWisdom += wisdom;
        user->abilityLuck += luck;
        user->maxHealth += health;
        user->maxMana += mana;
        user->maxStamina += stamina;
        user->attackAdd.power += attackPower;
        user->attackAddRanged.power += rangedAttackPower;
        user->attackAddMagic.power += magicPower;
        user->attack.defense += defense;
        user->attackRanged.defense += rangedDefense;
        user->attackMagic.defense += magicDefense;

        if (reaction)
            user->maxHealth += reaction * 5;

        if (wisdom)
            user->maxMana += wisdom * 5;

        if (dexterity)
            user->maxStamina += dexterity * 5;
    }

    if (!user->initStatusFlag)
    {
        if (maxHealth != user->maxHealth)
            CUser::SendMaxHP(user);

        if (maxMana != user->maxMana)
            CUser::SendMaxMP(user);

        if (maxStamina != user->maxStamina)
            CUser::SendMaxSP(user);
    }
}

void Synergy::getSynergies(CUser* user, std::vector<ItemSetSynergy>& synergies)
{
    for (const auto& itemSet : g_itemSets)
    {
        auto& equipment = user->inventory[0];
        auto count = std::count_if(equipment.cbegin(), equipment.cend(), ItemSetEqualToF(itemSet.id));

        auto maxCount = std::ssize(itemSet.synergies);
        if (!count || count > maxCount)
            continue;

        auto offset = maxCount - count;
        auto first = itemSet.synergies.crbegin() + offset;
        auto last = itemSet.synergies.crend();

        auto it = std::find_if_not(first, last, [](const auto& synergy) {
            return std::all_of(synergy.effects.cbegin(), synergy.effects.cend(), ext::unary_equal_to(0));
            });

        if (it == last)
            continue;

        synergies.push_back(*it);
    }
}
