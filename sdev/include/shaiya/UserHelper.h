#pragma once
#include "MoveType.h"

namespace shaiya
{
    struct ChaoticSquareRecipe;
    struct CUser;
    struct ItemInfo;
    struct SVector;

    struct UserHelper
    {
        /// <summary>
        ///  CUser::IsBag (EP4)
        /// </summary>
        static bool IsBag(CUser* user, int bag, int slot);
        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, int bag, int slot, int count);
        static bool SetMovePosition(CUser* user, MoveType moveType, unsigned delay, int mapId, float x, float y, float z);
        static bool RecipeRemove(CUser* user, const ChaoticSquareRecipe& recipe);
    };
}
