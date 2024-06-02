#pragma once
#include <array>
#include <fstream>
#include <map>
#include <vector>

#include <include/shaiya/include/DataFile.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    struct SynergyAbility
    {
        int strength;
        int dexterity;
        int intelligence;
        int wisdom;
        int reaction;
        int luck;
        int health;
        int mana;
        int stamina;
        int attackPower;
        int rangedAttackPower;
        int magicPower;

        constexpr std::size_t count()
        {
            return sizeof(SynergyAbility) / sizeof(int);
        }

        bool isNull() const noexcept
        {
            SynergyAbility ability{};
            return !std::memcmp(this, &ability, sizeof(SynergyAbility));
        }
    };

    struct Synergy : DataFile
    {
        UINT16 id;
        std::array<SynergyAbility, 13> abilities{};
        std::array<ItemId, 13> set{};

        static void init();
        static void applySynergies(CUser* user, CItem* item, bool itemRemove);
        static void removeSynergies(CUser* user);

    private:

        static void getWornSynergies(CUser* user, CItem* item, bool itemRemove, std::vector<SynergyAbility>& synergies);
        static void parseAbility(std::ifstream& ifs, SynergyAbility& ability);
    };

    inline std::vector<Synergy> g_synergies;
    inline std::map<CharId, std::vector<SynergyAbility>> g_appliedSynergies;
}
