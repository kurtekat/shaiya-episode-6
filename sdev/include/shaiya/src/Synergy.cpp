#include <array>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
#include "include/shaiya/include/SLog.h"
#include "include/shaiya/include/Synergy.h"
using namespace shaiya;

void Synergy::init()
{
    std::array<char, MAX_PATH> fileName{};
    GetModuleFileNameA(nullptr, fileName.data(), fileName.size());

    std::filesystem::path path(fileName.data());
    path.remove_filename();
    path.append("Data");
    path.append("SetItem.SData");

    if (!std::filesystem::exists(path))
        return;

    try
    {
        std::ifstream ifs;
        ifs.open(path, std::ios::binary);

        if (ifs.fail())
            return;

        uint32_t recordCount{};
        ifs.read(reinterpret_cast<char*>(&recordCount), 4);

        for (int i = 0; std::cmp_less(i, recordCount); ++i)
        {
            uint16_t id{};
            ifs.read(reinterpret_cast<char*>(&id), 2);

            Synergy synergy{};
            synergy.id = id;

            uint32_t nameLength{};
            ifs.read(reinterpret_cast<char*>(&nameLength), 4);
            ifs.ignore(nameLength);

            for (auto& itemId : synergy.set)
            {
                uint16_t type{}, typeId{};
                ifs.read(reinterpret_cast<char*>(&type), 2);
                ifs.read(reinterpret_cast<char*>(&typeId), 2);
                itemId = (type * 1000) + typeId;
            }

            for (auto& effect : synergy.effects)
            {
                uint32_t descLength{};
                ifs.read(reinterpret_cast<char*>(&descLength), 4);

                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                std::string desc(descLength, '\0');
                ifs.read(desc.data(), desc.size());

                auto vec = util::split(desc, ',');
                if (vec.size() != effect.size())
                    continue;

                for (int i = 0; std::cmp_less(i, effect.size()); ++i)
                    effect[i] = util::atoi(vec[i]);
            }

            g_synergies.push_back(synergy);
        }

        ifs.close();
    }
    catch (...)
    {
        g_synergies.clear();
    }
}

void Synergy::applySynergies(CUser* user, CItem* item, bool removeFlag)
{
    Synergy::removeSynergies(user);

    std::vector<SynergyEffect> effects{};
    Synergy::getWornSynergies(user, item, effects, removeFlag);

    if (effects.empty())
        return;

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

    g_appliedSynergies.insert_or_assign(user->connection.object.id, effects);
}

void Synergy::removeSynergies(CUser* user)
{
    auto it = g_appliedSynergies.find(user->connection.object.id);
    if (it == g_appliedSynergies.end())
        return;

    auto maxHealth = user->maxHealth;
    auto maxMana = user->maxHealth;
    auto maxStamina = user->maxHealth;

    for (const auto& effect : it->second)
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

void Synergy::getWornSynergies(CUser* user, CItem* item, std::vector<SynergyEffect>& effects, bool removeFlag)
{
    std::set<ItemId> equipment;
    for (const auto& wornItem : user->inventory[0])
    {
        if (!wornItem)
            continue;

        if (removeFlag)
        {
            if (wornItem == item)
                continue;
        }

        auto itemId = (wornItem->type * 1000) + wornItem->typeId;
        equipment.insert(itemId);
    }

    for (auto& synergy : g_synergies)
    {
        int wornCount = 0;
        for (const auto& itemId : synergy.set)
        {
            if (equipment.count(itemId))
                ++wornCount;
        }

        int index = wornCount - 1;
        if (index < 1 || index >= int(synergy.effects.size()))
            continue;

        for (int i = index; i > 0; --i)
        {
            auto& effect = synergy.effects[i];
            if (std::all_of(effect.begin(), effect.end(), [](auto& e) { return !e; }))
                continue;

            effects.push_back(effect);
            break;
        }
    }
}
