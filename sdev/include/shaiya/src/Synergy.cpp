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
#include <util/io/io.h>
#include <shaiya/include/common/SLog.h>
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
#include "include/shaiya/include/Synergy.h"
using namespace shaiya;

void Synergy::init()
{
    std::vector<char> vec(MAX_PATH);
    GetModuleFileNameA(nullptr, vec.data(), vec.size());

    std::filesystem::path path(vec.data());
    path.remove_filename();
    path.append("Data/SetItem.SData");

    if (!std::filesystem::exists(path))
    {
        SLog::PrintFileDirect(&g_pClientToLog->log, "cannot %s %s: %s", "open", ".\\Data\\SetItem.SData", "No such file or directory");
        return;
    }

    try
    {
        std::ifstream ifs;
        ifs.open(path, std::ios::binary);

        if (ifs.fail())
            return;

        auto records = util::io::read<uint32_t>(ifs);
        for (int i = 0; std::cmp_less(i, records); ++i)
        {
            Synergy synergy{};
            synergy.id = util::io::read<uint16_t>(ifs);

            // skip the set name
            util::io::readUcsdString<uint32_t>(ifs);

            for (auto& itemId : synergy.set)
            {
                auto type = util::io::read<uint16_t>(ifs);
                auto typeId = util::io::read<uint16_t>(ifs);
                itemId = (type * 1000) + typeId;
            }

            for (auto& effect : synergy.effects)
            {
                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                auto text = util::io::readUcsdString<uint32_t>(ifs);

                std::vector<int> vec{};
                for (const auto& token : std::views::split(text, ','))
                    vec.push_back(std::atoi(token.data()));

                if (vec.size() != 12)
                    continue;

                effect.none = std::all_of(vec.begin(), vec.end(), [](int& effect) {
                    return !effect;
                    });

                if (effect.none)
                    continue;

                effect.strength = vec[0];
                effect.dexterity = vec[1];
                effect.reaction = vec[2];
                effect.intelligence = vec[3];
                effect.wisdom = vec[4];
                effect.luck = vec[5];
                effect.health = vec[6];
                effect.mana = vec[7];
                effect.stamina = vec[8];
                effect.attackPower = vec[9];
                effect.rangedAttackPower = vec[10];
                effect.magicPower = vec[11];
            }

            g_synergies.push_back(synergy);
        }

        ifs.close();
    }
    catch (...)
    {
    }
}

void Synergy::applySynergies(CUser* user, CItem* item, bool itemRemove)
{
    Synergy::removeSynergies(user);

    std::vector<SynergyEffect> effects{};
    Synergy::getWornSynergies(user, item, itemRemove, effects);

    if (effects.empty())
        return;

    for (const auto& effect : effects)
    {
        user->abilityStrength += effect.strength;
        user->abilityDexterity += effect.dexterity;
        user->abilityReaction += effect.reaction;
        user->abilityIntelligence += effect.intelligence;
        user->abilityWisdom += effect.wisdom;
        user->abilityLuck += effect.luck;
        user->maxHealth += effect.health;
        user->maxMana += effect.mana;
        user->maxStamina += effect.stamina;
        user->abilityAttackPower += effect.attackPower;
        user->abilityRangedAttackPower += effect.rangedAttackPower;
        user->abilityMagicPower += effect.magicPower;

        if (effect.reaction)
            user->maxHealth += effect.reaction * 5;

        if (effect.wisdom)
            user->maxMana += effect.wisdom * 5;

        if (effect.dexterity)
            user->maxStamina += effect.dexterity * 5;
    }

    g_appliedSynergies.insert_or_assign(user->id, effects);
}

void Synergy::removeSynergies(CUser* user)
{
    auto it = g_appliedSynergies.find(user->id);
    if (it == g_appliedSynergies.end())
        return;

    for (const auto& effect : it->second)
    {
        user->abilityStrength -= effect.strength;
        user->abilityDexterity -= effect.dexterity;
        user->abilityReaction -= effect.reaction;
        user->abilityIntelligence -= effect.intelligence;
        user->abilityWisdom -= effect.wisdom;
        user->abilityLuck -= effect.luck;
        user->maxHealth -= effect.health;
        user->maxMana -= effect.mana;
        user->maxStamina -= effect.stamina;
        user->abilityAttackPower -= effect.attackPower;
        user->abilityRangedAttackPower -= effect.rangedAttackPower;
        user->abilityMagicPower -= effect.magicPower;

        if (effect.reaction)
            user->maxHealth -= effect.reaction * 5;

        if (effect.wisdom)
            user->maxMana -= effect.wisdom * 5;

        if (effect.dexterity)
            user->maxStamina -= effect.dexterity * 5;
    }

    g_appliedSynergies.erase(user->id);
}

void Synergy::getWornSynergies(CUser* user, CItem* item, bool itemRemove, std::vector<SynergyEffect>& effects)
{
    std::set<ItemId> equipment;
    for (const auto& wornItem : user->inventory[0])
    {
        if (!wornItem)
            continue;

        if (wornItem == item && itemRemove)
            continue;

        auto itemId = (wornItem->type * 1000) + wornItem->typeId;
        equipment.insert(itemId);
    }

    for (auto& synergy : g_synergies)
    {
        std::size_t wornCount = 0;
        for (const auto& itemId : synergy.set)
        {
            if (equipment.count(itemId))
                ++wornCount;
        }

        if (wornCount > synergy.effects.size())
            continue;

        if (wornCount < 2)
            continue;

        for (int i = wornCount - 1; i > 0; --i)
        {
            auto& effect = synergy.effects[i];
            if (effect.none)
                continue;

            effects.push_back(effect);
            break;
        }
    }
}
