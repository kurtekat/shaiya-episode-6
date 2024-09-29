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
    {
        SLog::PrintFileDirect(&g_pClientToLog->log, "Synergy::init : %s does not exist", path.string().c_str());
        return;
    }

    try
    {
        std::ifstream ifs;
        ifs.open(path, std::ios::binary);

        if (ifs.fail())
            return;

        uint32_t records{};
        ifs.read(reinterpret_cast<char*>(&records), 4);

        for (int i = 0; std::cmp_less(i, records); ++i)
        {
            Synergy synergy{};
            ifs.read(reinterpret_cast<char*>(&synergy.id), 2);

            uint32_t length{};
            ifs.read(reinterpret_cast<char*>(&length), 4);
            ifs.ignore(length);

            for (auto& itemId : synergy.set)
            {
                uint16_t type{}, typeId{};
                ifs.read(reinterpret_cast<char*>(&type), 2);
                ifs.read(reinterpret_cast<char*>(&typeId), 2);
                itemId = (type * 1000) + typeId;
            }

            for (auto& effect : synergy.effects)
            {
                uint32_t length{};
                ifs.read(reinterpret_cast<char*>(&length), 4);

                // e.g., 70,50,0,0,0,20,0,0,0,0,0,0
                std::string text(length, '\0');
                ifs.read(text.data(), text.size());

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
    catch (const std::exception& ex)
    {
        SLog::PrintFileDirect(&g_pClientToLog->log, "Synergy::init : %s", ex.what());
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
            if (effect.none)
                continue;

            effects.push_back(effect);
            break;
        }
    }
}
