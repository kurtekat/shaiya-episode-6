#pragma once
#include <shaiya/include/common/ItemSlot.h>

namespace shaiya
{
    struct CUser;

    template<class Predicate>
    inline bool ItemFinder(CUser* user, int& outBag, int& outSlot, Predicate predicate)
    {
        outBag = 1;
        while (outBag <= user->bagsUnlocked)
        {
            for (outSlot = 0; outSlot < ItemSlotCount; ++outSlot)
            {
                auto& item = user->inventory[outBag][outSlot];
                if (!item)
                    continue;

                if (predicate(item))
                    return true;
            }

            ++outBag;
        }

        return false;
    }
}
