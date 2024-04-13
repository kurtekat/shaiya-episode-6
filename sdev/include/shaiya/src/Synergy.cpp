#include <array>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnectionTBaseReconnect.h>
#include <include/shaiya/include/SLog.h>
#include <include/shaiya/include/Synergy.h>
#include <util/include/util.h>
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

        auto records = readNumber<std::uint32_t>(ifs);
        for (auto i = 0U; i < records; ++i)
        {
            Synergy synergy{};
            synergy.id = readNumber<std::uint16_t>(ifs);

            readPascalString(ifs);

            for (auto& itemId : synergy.set)
            {
                auto type = readNumber<std::uint16_t>(ifs);
                auto typeId = readNumber<std::uint16_t>(ifs);

                itemId = (type * 1000) + typeId;
            }

            for (auto& ability : synergy.ability)
                Synergy::parseAbility(ifs, ability);

            g_synergies.push_back(synergy);
        }

        ifs.close();
    }
    catch (...)
    {
    }
}

void Synergy::parseAbility(std::ifstream& ifs, SynergyAbility& ability)
{
    auto text = readPascalString(ifs);
    if (text == "0" || text.empty())
        return;

    std::istringstream iss(text);
    std::vector<int> vec{};
    for (std::string str; std::getline(iss, str, ','); )
        vec.push_back(std::atoi(str.c_str()));

    if (vec.size() != ability.count())
        return;

    std::memcpy(&ability, vec.data(), sizeof(SynergyAbility));
}

void Synergy::applySynergies(CUser* user)
{
    Synergy::removeSynergies(user);

    std::vector<SynergyAbility> synergies{};
    Synergy::getWornSynergies(user, synergies);

    if (synergies.empty())
        return;

    for (const auto& ability : synergies)
    {
        user->abilityStrength += ability.strength;
        user->abilityDexterity += ability.dexterity;
        user->abilityReaction += ability.reaction;
        user->abilityIntelligence += ability.intelligence;
        user->abilityWisdom += ability.wisdom;
        user->abilityLuck += ability.luck;
        user->maxHealth += ability.health;
        user->maxMana += ability.mana;
        user->maxStamina += ability.stamina;
        user->abilityAttackPower += ability.attackPower;
        user->abilityRangedAttackPower += ability.rangedAttackPower;
        user->abilityMagicPower += ability.magicPower;

        if (ability.reaction)
            user->maxHealth += ability.reaction * 5;

        if (ability.wisdom)
            user->maxMana += ability.wisdom * 5;

        if (ability.dexterity)
            user->maxStamina += ability.dexterity * 5;
    }

    g_appliedSynergies.insert_or_assign(user->id, synergies);
}

void Synergy::removeSynergies(CUser* user)
{
    auto it = g_appliedSynergies.find(user->id);
    if (it == g_appliedSynergies.end())
        return;

    for (const auto& ability : it->second)
    {
        user->abilityStrength -= ability.strength;
        user->abilityDexterity -= ability.dexterity;
        user->abilityReaction -= ability.reaction;
        user->abilityIntelligence -= ability.intelligence;
        user->abilityWisdom -= ability.wisdom;
        user->abilityLuck -= ability.luck;
        user->maxHealth -= ability.health;
        user->maxMana -= ability.mana;
        user->maxStamina -= ability.stamina;
        user->abilityAttackPower -= ability.attackPower;
        user->abilityRangedAttackPower -= ability.rangedAttackPower;
        user->abilityMagicPower -= ability.magicPower;

        if (ability.reaction)
            user->maxHealth -= ability.reaction * 5;

        if (ability.wisdom)
            user->maxMana -= ability.wisdom * 5;

        if (ability.dexterity)
            user->maxStamina -= ability.dexterity * 5;
    }

    g_appliedSynergies.erase(user->id);
}

void Synergy::getWornSynergies(CUser* user, std::vector<SynergyAbility>& synergies)
{
    std::set<ItemId> equipment;
    for (const auto& item : user->inventory[0])
    {
        if (!item)
            continue;

        auto itemId = (item->type * 1000U) + item->typeId;
        equipment.insert(itemId);
    }

    for (auto& synergy : g_synergies)
    {
        int wornCount = 0;
        for (const auto& itemId : synergy.set)
            if (equipment.count(itemId))
                ++wornCount;

        if (wornCount < 2)
            continue;

        for (int i = wornCount - 1; i > 0; --i)
        {
            if (synergy.ability[i].isNull())
                continue;
            
            synergies.push_back(synergy.ability[i]);
            break;
        }
    }
}
