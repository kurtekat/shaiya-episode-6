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
        static bool HasApplySkill(CUser* user, int skillId, int skillLv);

        static bool ItemCreate(CUser* user, ItemInfo* itemInfo, int count, int& outBag, int& outSlot);
        static bool ItemRemove(CUser* user, int bag, int slot, int count);
        static bool ItemRemove(CUser* user, ItemId itemId, int count);
        static bool ItemRemove(CUser* user, ItemEffect effect, int count);

        static void SetMovePosition(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay);
        static void SetMovePosition(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay);
        static bool Teleport(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay);
        static bool Teleport(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay);
    };
}
