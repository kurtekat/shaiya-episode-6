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
        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, uint8_t count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, uint8_t bag, uint8_t slot, uint8_t count);
        static bool ItemRemove(CUser* user, ItemInfo* itemInfo, uint8_t count);
        static bool ItemRemove(CUser* user, ItemEffect itemEffect, uint8_t count);

        static void SetMovePosition(CUser* user, uint16_t mapId, float x, float y, float z, int movePosType, uint delay);
        static void SetMovePosition(CUser* user, uint16_t mapId, SVector* pos, int movePosType, uint delay);
        static bool Move(CUser* user, uint16_t mapId, float x, float y, float z, int movePosType, uint delay);
        static bool Move(CUser* user, uint16_t mapId, SVector* pos, int movePosType, uint delay);
    };
}
