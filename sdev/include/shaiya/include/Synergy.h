#pragma once
#include <array>
#include <map>
#include <vector>
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;
    
    #pragma pack(push, 1)
    struct SynergyEffect
    {
        int strength{ 0 };
        int dexterity{ 0 };
        int intelligence{ 0 };
        int wisdom{ 0 };
        int reaction{ 0 };
        int luck{ 0 };
        int health{ 0 };
        int mana{ 0 };
        int stamina{ 0 };
        int attackPower{ 0 };
        int rangedAttackPower{ 0 };
        int magicPower{ 0 };

        bool none{ true };
    };
    #pragma pack(pop)

    class Synergy
    {
    public:

        int id;
        std::array<SynergyEffect, 13> effects{};
        std::array<ItemId, 13> set{};

        static void init();
        static void applySynergies(CUser* user, CItem* item, bool removeFlag);
        static void removeSynergies(CUser* user);

        Synergy()
            : id(0)
        {
        }

    private:

        static void getWornSynergies(CUser* user, CItem* item, std::vector<SynergyEffect>& effects, bool removeFlag);
    };

    inline std::vector<Synergy> g_synergies;
    inline std::map<CharId, std::vector<SynergyEffect>> g_appliedSynergies;
}
