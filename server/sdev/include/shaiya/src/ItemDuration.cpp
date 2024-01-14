#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/ItemDuration.h>

bool shaiya::ItemHasDuration(CGameData::ItemInfo* itemInfo)
{
    if (!itemInfo)
        return false;

    if (!itemInfo->range)
        return false;

    switch (static_cast<CGameData::ItemType>(itemInfo->type))
    {
    case CGameData::ItemType::Pet:
    case CGameData::ItemType::Costume:
        return true;
    default:
        break;
    }

    return false;
}
