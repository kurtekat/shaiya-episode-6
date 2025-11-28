#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    static unsigned g_GameData = 0x587C68;
    // item effect 59 (EP5 itemId 100169)
    static unsigned g_ItemSpecialMoveWar = 0x56E668;

    struct ItemInfo;
    struct MobInfo;
    struct ProductInfo;
    struct SkillInfo;

    struct CGameData
    {
        static unsigned GetExp(int grow, int level);
        static ItemInfo* GetItemInfo(int type/*eax*/, int typeId/*ecx*/);
        static MobInfo* GetMobInfo(int mobId/*eax*/);
        static ProductInfo* GetProductInfo(const char* productCode/*eax*/);
        static SkillInfo* GetSkillInfo(int skillId/*eax*/, int skillLv/*edx*/);
    };
}
