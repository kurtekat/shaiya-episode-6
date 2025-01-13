#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    struct CItem;

    class ItemHelper
    {
    public:

        static void SetCraftStrength(CItem* item, UINT16 value);
        static void SetCraftDexterity(CItem* item, UINT16 value);
        static void SetCraftReaction(CItem* item, UINT16 value);
        static void SetCraftIntelligence(CItem* item, UINT16 value);
        static void SetCraftWisdom(CItem* item, UINT16 value);
        static void SetCraftLuck(CItem* item, UINT16 value);
        static void SetCraftHealth(CItem* item, UINT16 value);
        static void SetCraftMana(CItem* item, UINT16 value);
        static void SetCraftStamina(CItem* item, UINT16 value);
        //static void SetCraftAttackPower(CItem* item, UINT16 value);
        //static void SetCraftAbsorption(CItem* item, UINT16 value);

        static void CopyCraftName(CItem* from, CItem* to);
        static void InitCraftName(CItem* item);
    };
}
