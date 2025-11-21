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
        static bool FindItem(CUser* user, int type, int typeId, uint_t count, int& outBag, int& outSlot);
        static bool FindItem(CUser* user, ItemEffect itemEffect, uint_t count, int& outBag, int& outSlot);
        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, uint_t count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, uint_t bag, uint_t slot, uint_t count);
        static void SetMovePosition(CUser* user, uint_t mapId, float x, float y, float z, UserMovePosType movePosType, uint_t delay);
        static void SetMovePosition(CUser* user, uint_t mapId, SVector* pos, UserMovePosType movePosType, uint_t delay);
        static bool Move(CUser* user, uint_t mapId, float x, float y, float z, UserMovePosType movePosType, uint_t delay);
        static bool Move(CUser* user, uint_t mapId, SVector* pos, UserMovePosType movePosType, uint_t delay);
    };
}
