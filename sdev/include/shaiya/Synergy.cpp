#include <algorithm>
#include <map>
#include <ranges>
#include <set>
#include <vector>
#include "CItem.h"
#include "CUser.h"
#include "Synergy.h"
using namespace shaiya;

void Synergy::equipmentAdd(CUser* user)
{
    Synergy::removeSynergies(user);

    std::set<ItemId> equipment;
    Synergy::getWornEquipment(user, equipment);

    if (equipment.empty())
        return;

    std::vector<ItemSetSynergy> synergies;
    Synergy::getWornSynergies(equipment, synergies);

    if (synergies.empty())
        return;

    Synergy::applySynergies(user, synergies);
}

void Synergy::equipmentRemove(CUser* user, int slot)
{
    Synergy::removeSynergies(user);

    std::set<ItemId> equipment;
    for (const auto& [_, item] : std::views::enumerate(
        std::as_const(user->inventory[0])))
    {
        if (!item)
            continue;

        if (_ == slot)
            continue;

        auto itemId = (item->type * 1000) + item->typeId;
        equipment.insert(itemId);
    }

    if (equipment.empty())
        return;

    std::vector<ItemSetSynergy> synergies;
    Synergy::getWornSynergies(equipment, synergies);

    if (synergies.empty())
        return;

    Synergy::applySynergies(user, synergies);
}

void Synergy::removeSynergies(CUser* user)
{
    auto it = g_itemSetSynergies.find(user->id);
    if (it == g_itemSetSynergies.end())
        return;

    auto maxHealth = user->maxHealth;
    auto maxMana = user->maxHealth;
    auto maxStamina = user->maxHealth;

    auto& synergies = it->second;
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

    g_itemSetSynergies.erase(user->id);
}

void Synergy::applySynergies(CUser* user, const std::vector<ItemSetSynergy>& synergies)
{
    if (g_itemSetSynergies.count(user->id))
        Synergy::removeSynergies(user);

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

    g_itemSetSynergies.insert({ user->id, synergies });
}

void Synergy::getWornEquipment(CUser* user, std::set<ItemId>& equipment)
{
    for (const auto& item : user->inventory[0])
    {
        if (!item)
            continue;

        auto itemId = (item->type * 1000) + item->typeId;
        equipment.insert(itemId);
    }
}

void Synergy::getWornSynergies(const std::set<ItemId>& equipment, std::vector<ItemSetSynergy>& synergies)
{
    if (equipment.empty())
        return;

    for (const auto& itemSet : g_itemSets)
    {
        size_t wornCount = 0;
        for (const auto& itemId : itemSet.items)
        {
            if (equipment.contains(itemId))
                ++wornCount;
        }

        size_t size = itemSet.synergies.size();
        if (!wornCount || wornCount > size)
            continue;

        auto offset = size - wornCount;
        auto first = itemSet.synergies.crbegin() + offset;
        auto last = itemSet.synergies.crend();

        auto it = std::find_if(first, last, [](const auto& synergy) {
            return !std::all_of(synergy.effects.cbegin(), synergy.effects.cend(), [](const auto& effect) {
                return !effect;
                });
            });

        if (it == last)
            continue;

        synergies.push_back(*it);
    }
}
