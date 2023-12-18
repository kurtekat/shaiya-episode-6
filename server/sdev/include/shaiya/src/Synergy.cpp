#include <array>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <include/util.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/Synergy.h>
using namespace shaiya;

void Synergy::init()
{
    std::filesystem::path path(std::filesystem::current_path().append("Data/SetItem.SData"));
    std::ifstream ifs(path, std::ios::binary);

    if (ifs.fail())
    {
        util::log("Synergy::init open failure");
        return;
    }

    try
    {
        auto entries = util::read_number<int>(ifs);

        for (int i = 0; i < entries; ++i)
        {
            Synergy synergy{};
            synergy.id = util::read_number<std::uint16_t>(ifs);

            util::read_pascal_string(ifs);

            for (int i = 0; i < 13; ++i)
            {
                auto type = util::read_number<std::uint16_t>(ifs);
                auto typeId = util::read_number<std::uint16_t>(ifs);

                auto itemId = (type * 1000) + typeId;
                synergy.set[i] = itemId;
            }

            for (int i = 0; i < 13; ++i)
                Synergy::parseAbility(ifs, synergy.ability[i]);

            g_synergies.push_back(synergy);
        }
    }
    catch (const std::exception& ex)
    {
        std::string text("Synergy::init read failure\n");
        util::log(text.append(ex.what()));
    }
}

void Synergy::parseAbility(std::ifstream& ifs, SynergyAbility& ability)
{
    auto text = util::read_pascal_string(ifs);
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

    auto& bag = user->inventory[0];
    for (const auto& item : bag)
    {
        if (!item)
            continue;

        equipment.insert(item->itemInfo->itemId);
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
