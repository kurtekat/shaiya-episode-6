#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/ItemDuration.h>

bool shaiya::ItemHasDuration(CGameData::ItemInfo* itemInfo)
{
    if (!itemInfo)
        return false;

    // see absorption lapis
    if (itemInfo->type == 30 || !itemInfo->exp)
        return false;

    return true;
}
