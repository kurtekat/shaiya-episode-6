#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    struct CUser;
    struct ItemInfo;
    struct SVector;

    struct UserHelper
    {
        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, int bag, int slot, int count);
        static bool ItemRemove(CUser* user, uint itemId, int count);
        static bool ItemRemove(CUser* user, ItemEffect itemEffect, int count);

        static void SetMovePosition(CUser* user, int mapId, float x, float y, float z, int movePosType, uint delay);
        static void SetMovePosition(CUser* user, int mapId, SVector* pos, int movePosType, uint delay);
        static bool Move(CUser* user, int mapId, float x, float y, float z, int movePosType, uint delay);
        static bool Move(CUser* user, int mapId, SVector* pos, int movePosType, uint delay);
    };
}
