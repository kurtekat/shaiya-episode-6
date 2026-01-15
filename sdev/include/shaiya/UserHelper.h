#pragma once
#include "CUser.h"

namespace shaiya
{
    struct ChaoticSquareRecipe;
    struct ItemInfo;
    struct SVector;

    struct UserHelper
    {
        static bool IsValidItemPosition(CUser* user, int bag, int slot);
        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, int bag, int slot, int count);
        static void SetMovePosition(CUser* user, unsigned mapId, float x, float y, float z, UserMovePosType movePosType, unsigned delay);
        static void SetMovePosition(CUser* user, unsigned mapId, SVector* pos, UserMovePosType movePosType, unsigned delay);
        static bool Move(CUser* user, unsigned mapId, float x, float y, float z, UserMovePosType movePosType, unsigned delay);
        static bool Move(CUser* user, unsigned mapId, SVector* pos, UserMovePosType movePosType, unsigned delay);
        static bool RecipeRemove(CUser* user, const ChaoticSquareRecipe& recipe);
    };
}
