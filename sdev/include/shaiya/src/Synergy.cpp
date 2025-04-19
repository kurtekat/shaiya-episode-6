#include <filesystem>
#include <fstream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/string_helper.h>
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Synergy.h"
using namespace shaiya;

void Synergy::init()
{
    try
    {
        std::wstring buffer(INT16_MAX, 0);
        if (!GetModuleFileNameW(nullptr, buffer.data(), INT16_MAX))
            return;

        std::filesystem::path path(buffer);
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
                uint32_t textLength{};
                sdata.read(reinterpret_cast<char*>(&textLength), 4);

                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                std::string text(textLength, '\0');
                sdata.read(text.data(), text.size());

                auto vec = util::split(text, ',');
                if (vec.size() != effect.size())
                    continue;

                for (int i = 0; std::cmp_less(i, effect.size()); ++i)
                    effect[i] = std::stoi(vec[i]);
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
