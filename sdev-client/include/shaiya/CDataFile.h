#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct ItemInfo;
    struct MobInfo;
    struct SkillInfo;

    struct CDataFile
    {
        static ItemInfo* GetItemInfo(int type, int typeId);
        static MobInfo* GetMobInfo(int mobId);
        static SkillInfo* GetSkillInfo(int skillId, int skillLv);
    };
}
