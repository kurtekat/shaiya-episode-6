#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    class ItemHelper
    {
    public:

        static void SetCraftStrength(CItem* item, uint_t value);
        static void SetCraftDexterity(CItem* item, uint_t value);
        static void SetCraftReaction(CItem* item, uint_t value);
        static void SetCraftIntelligence(CItem* item, uint_t value);
        static void SetCraftWisdom(CItem* item, uint_t value);
        static void SetCraftLuck(CItem* item, uint_t value);
        static void SetCraftHealth(CItem* item, uint_t value);
        static void SetCraftMana(CItem* item, uint_t value);
        static void SetCraftStamina(CItem* item, uint_t value);
        //static void SetCraftAttackPower(CItem* item, uint_t value);
        //static void SetCraftAbsorption(CItem* item, uint_t value);

        static void CopyCraftExpansion(CItem* src, CItem* dest);
        static void InitCraftExpansion(CItem* item);

        static void SendDBAgentCraftName(CUser* user, CItem* item, uint_t bag, uint_t slot);
        static void SendDBAgentGems(CUser* user, CItem* item, uint_t bag, uint_t slot);
        static void SendDBAgentCloakInfo(CUser* user, CItem* item, uint_t bag, uint_t slot);
    };
}
