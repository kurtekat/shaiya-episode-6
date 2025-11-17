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

    std::vector<StatusEffects> effects;
    Synergy::getWornSynergies(equipment, effects);

    if (effects.empty())
        return;

    Synergy::applySynergies(user, effects);
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

    std::vector<StatusEffects> effects;
    Synergy::getWornSynergies(equipment, effects);

    if (effects.empty())
        return;

    Synergy::applySynergies(user, effects);
}

void Synergy::removeSynergies(CUser* user)
{
    auto it = g_appliedSynergies.find(user->id);
    if (it == g_appliedSynergies.end())
        return;

    auto maxHealth = user->maxHealth;
    auto maxMana = user->maxHealth;
    auto maxStamina = user->maxHealth;

    auto& effects = it->second;
    for (const auto& effect : effects)
    {
        auto strength = effect[0];
        auto dexterity = effect[1];
        auto reaction = effect[2];
        auto intelligence = effect[3];
        auto wisdom = effect[4];
        auto luck = effect[5];
        auto health = effect[6];
        auto mana = effect[7];
        auto stamina = effect[8];
        auto attackPower = effect[9];
        auto rangedAttackPower = effect[10];
        auto magicPower = effect[11];

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

    g_appliedSynergies.erase(user->id);
}

void Synergy::applySynergies(CUser* user, const std::vector<StatusEffects>& effects)
{
    if (g_appliedSynergies.count(user->id))
        Synergy::removeSynergies(user);

    auto maxHealth = user->maxHealth;
    auto maxMana = user->maxHealth;
    auto maxStamina = user->maxHealth;

    for (const auto& effect : effects)
    {
        auto strength = effect[0];
        auto dexterity = effect[1];
        auto reaction = effect[2];
        auto intelligence = effect[3];
        auto wisdom = effect[4];
        auto luck = effect[5];
        auto health = effect[6];
        auto mana = effect[7];
        auto stamina = effect[8];
        auto attackPower = effect[9];
        auto rangedAttackPower = effect[10];
        auto magicPower = effect[11];

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

    g_appliedSynergies.insert({ user->id, effects });
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

void Synergy::getWornSynergies(const std::set<ItemId>& equipment, std::vector<StatusEffects>& effects)
{
    if (equipment.empty())
        return;

    for (const auto& synergy : g_synergies)
    {
        int wornCount = 0;
        for (const auto& itemId : synergy.set)
        {
            if (equipment.count(itemId))
                ++wornCount;
        }

        if (!wornCount)
            continue;

        --wornCount;
        if (!wornCount || std::cmp_greater_equal(wornCount, synergy.effects.size()))
            continue;

        for (int i = wornCount; i > 0; --i)
        {
            auto& effect = synergy.effects[i];
            if (std::all_of(effect.begin(), effect.end(), [](auto& e) { return !e; }))
                continue;

            effects.push_back(effect);
            break;
        }
    }
}
