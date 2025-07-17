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
        static bool FindItem(CUser* user, int type, int typeId, uint count, int& outBag, int& outSlot);
        static bool FindItem(CUser* user, ItemEffect itemEffect, uint count, int& outBag, int& outSlot);
        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, uint count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, uint bag, uint slot, uint count);
        static void SetMovePosition(CUser* user, uint mapId, float x, float y, float z, int movePosType, uint delay);
        static void SetMovePosition(CUser* user, uint mapId, SVector* pos, int movePosType, uint delay);
        static bool Move(CUser* user, uint mapId, float x, float y, float z, int movePosType, uint delay);
        static bool Move(CUser* user, uint mapId, SVector* pos, int movePosType, uint delay);
    };
}
