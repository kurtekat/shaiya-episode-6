#pragma once
#include <shaiya/include/common/ItemSlot.h>

namespace shaiya
{
    struct CUser;

    /// <summary>
    /// Finds the first instance of an item in the inventory that satisfies the unary predicate. 
    /// The bag and slot are returned in output parameters.
    /// </summary>
    template<class UnaryPred>
    inline bool ItemFinder(CUser* user, int& outBag, int& outSlot, UnaryPred pred)
    {
        for (outBag = 1; outBag <= user->bagsUnlocked; ++outBag)
        {
            for (outSlot = 0; outSlot < 24; ++outSlot)
            {
                auto& item = user->inventory[outBag][outSlot];
                if (!item)
                    continue;

                if (pred(item))
                    return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Finds the first instance of an item in the warehouse that satisfies the unary predicate. 
    /// The slot is returned in an output parameter.
    /// </summary>
    template<class UnaryPred>
    inline bool StoredItemFinder(CUser* user, int& outSlot, UnaryPred pred)
    {
        int slotCount = user->doubleWarehouse ? 240 : 120;
        for (outSlot = 0; outSlot < slotCount; ++outSlot)
        {
            auto& item = user->warehouse[outSlot];
            if (!item)
                continue;

            if (pred(item))
                return true;
        }

        return false;
    }
}
