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

        static void SetCraftStrength(CItem* item, uint value);
        static void SetCraftDexterity(CItem* item, uint value);
        static void SetCraftReaction(CItem* item, uint value);
        static void SetCraftIntelligence(CItem* item, uint value);
        static void SetCraftWisdom(CItem* item, uint value);
        static void SetCraftLuck(CItem* item, uint value);
        static void SetCraftHealth(CItem* item, uint value);
        static void SetCraftMana(CItem* item, uint value);
        static void SetCraftStamina(CItem* item, uint value);
        //static void SetCraftAttackPower(CItem* item, uint value);
        //static void SetCraftAbsorption(CItem* item, uint value);

        static void CopyCraftExpansion(CItem* src, CItem* dest);
        static void InitCraftExpansion(CItem* item);

        static void SendDBAgentCraftName(CUser* user, CItem* item, uint bag, uint slot);
        static void SendDBAgentGems(CUser* user, CItem* item, uint bag, uint slot);
        static void SendDBAgentCloakInfo(CUser* user, CItem* item, uint bag, uint slot);
    };
}
