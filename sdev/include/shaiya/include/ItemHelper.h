#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    struct CItem;

    class ItemHelper
    {
    public:

        static void SetCraftStrength(CItem* item, uint16_t value);
        static void SetCraftDexterity(CItem* item, uint16_t value);
        static void SetCraftReaction(CItem* item, uint16_t value);
        static void SetCraftIntelligence(CItem* item, uint16_t value);
        static void SetCraftWisdom(CItem* item, uint16_t value);
        static void SetCraftLuck(CItem* item, uint16_t value);
        static void SetCraftHealth(CItem* item, uint16_t value);
        static void SetCraftMana(CItem* item, uint16_t value);
        static void SetCraftStamina(CItem* item, uint16_t value);
        //static void SetCraftAttackPower(CItem* item, uint16_t value);
        //static void SetCraftAbsorption(CItem* item, uint16_t value);

        static void CopyCraftExpansion(CItem* src, CItem* dest);
        static void InitCraftExpansion(CItem* item);

        static void SendDBAgentCraftName(CUser* user, CItem* item, uint8_t bag, uint8_t slot);
        static void SendDBAgentGems(CUser* user, CItem* item, uint8_t bag, uint8_t slot);
        static void SendDBAgentCloakInfo(CUser* user, CItem* item, uint8_t bag, uint8_t slot);
    };
}
