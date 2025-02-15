#include <array>
#include <filesystem>
#include <fstream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Synergy.h"
using namespace shaiya;

void Synergy::init()
{
    try
    {
        std::array<char, MAX_PATH> fileName{};
        GetModuleFileNameA(nullptr, fileName.data(), fileName.size());

        std::filesystem::path path(fileName.data());
        path.remove_filename();
        path.append("Data");
        path.append("SetItem.SData");

        std::ifstream sdata(path, std::ios::binary);
        if (!sdata)
            return;

        uint32_t recordCount{};
        sdata.read(reinterpret_cast<char*>(&recordCount), 4);

        for (int i = 0; std::cmp_less(i, recordCount); ++i)
        {
            uint16_t id{};
            sdata.read(reinterpret_cast<char*>(&id), 2);

            Synergy synergy{};
            synergy.id = id;

            uint32_t nameLength{};
            sdata.read(reinterpret_cast<char*>(&nameLength), 4);
            sdata.ignore(nameLength);

            for (auto&& itemId : synergy.set)
            {
                uint16_t type{}, typeId{};
                sdata.read(reinterpret_cast<char*>(&type), 2);
                sdata.read(reinterpret_cast<char*>(&typeId), 2);
                itemId = (type * 1000) + typeId;
            }

            for (auto&& effect : synergy.effects)
            {
                uint32_t descLength{};
                sdata.read(reinterpret_cast<char*>(&descLength), 4);

                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                std::string desc(descLength, '\0');
                sdata.read(desc.data(), desc.size());

                auto vec = util::split(desc, ',');
                if (vec.size() != effect.size())
                    continue;

                for (int i = 0; std::cmp_less(i, effect.size()); ++i)
                    effect[i] = util::atoi(vec[i]);
            }

            g_synergies.push_back(synergy);
        }

        sdata.close();
    }
    catch (...)
    {
        g_synergies.clear();
    }
}

void Synergy::equipmentAdd(CUser* user)
{
    Synergy::removeSynergies(user);

    std::set<ItemId> equipment;
    Synergy::getWornEquipment(user, equipment);

    if (equipment.empty())
        return;

    std::vector<SynergyEffect> effects;
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

    std::vector<SynergyEffect> effects;
    Synergy::getWornSynergies(equipment, effects);

    if (effects.empty())
        return;

    Synergy::applySynergies(user, effects);
}

void Synergy::removeSynergies(CUser* user)
{
    auto it = g_appliedSynergies.find(user->connection.object.id);
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
        user->abilityAttackPower -= attackPower;
        user->abilityRangedAttackPower -= rangedAttackPower;
        user->abilityMagicPower -= magicPower;

        if (reaction)
            user->maxHealth -= reaction * 5;

        if (wisdom)
            user->maxMana -= wisdom * 5;

        if (dexterity)
            user->maxStamina -= dexterity * 5;
    }

    if (!user->ignoreMaxHpMpSpSpeed)
    {
        if (maxHealth != user->maxHealth)
            CUser::SendMaxHP(user);

        if (maxMana != user->maxMana)
            CUser::SendMaxMP(user);

        if (maxStamina != user->maxStamina)
            CUser::SendMaxSP(user);
    }

    g_appliedSynergies.erase(user->connection.object.id);
}

void Synergy::applySynergies(CUser* user, const std::vector<SynergyEffect>& effects)
{
    auto objectId = user->connection.object.id;
    if (g_appliedSynergies.count(objectId))
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
        user->abilityAttackPower += attackPower;
        user->abilityRangedAttackPower += rangedAttackPower;
        user->abilityMagicPower += magicPower;

        if (reaction)
            user->maxHealth += reaction * 5;

        if (wisdom)
            user->maxMana += wisdom * 5;

        if (dexterity)
            user->maxStamina += dexterity * 5;
    }

    if (!user->ignoreMaxHpMpSpSpeed)
    {
        if (maxHealth != user->maxHealth)
            CUser::SendMaxHP(user);

        if (maxMana != user->maxMana)
            CUser::SendMaxMP(user);

        if (maxStamina != user->maxStamina)
            CUser::SendMaxSP(user);
    }

    g_appliedSynergies.insert({ objectId, effects });
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

void Synergy::getWornSynergies(const std::set<ItemId>& equipment, std::vector<SynergyEffect>& effects)
{
    if (equipment.empty())
        return;

    for (const auto& synergy : g_synergies)
    {
        size_t wornCount = 0;
        for (const auto& itemId : synergy.set)
        {
            if (equipment.count(itemId))
                ++wornCount;
        }

        if (!wornCount)
            continue;

        --wornCount;
        if (!wornCount || wornCount >= synergy.effects.size())
            continue;

        for (auto i = wornCount; i > 0; --i)
        {
            auto& effect = synergy.effects[i];
            if (std::all_of(effect.begin(), effect.end(), [](auto& e) { return !e; }))
                continue;

            effects.push_back(effect);
            break;
        }
    }
}
