#include "CDataFile.h"
#include "ItemInfo.h"
#include "MobInfo.h"
#include "SkillInfo.h"
using namespace shaiya;

ItemInfo* CDataFile::GetItemInfo(int type, int typeId)
{
    typedef ItemInfo* (__thiscall* LPFN)(void*, int, int);
    return (*(LPFN)0x46CB30)((void*)0x91AD64, type, typeId);
}

MobInfo* CDataFile::GetMobInfo(int mobId)
{
    typedef MobInfo* (__thiscall* LPFN)(void*, int);
    return (*(LPFN)0x46CCA0)((void*)0x91AD64, mobId);
}

SkillInfo* CDataFile::GetSkillInfo(int skillId, int skillLv)
{
    typedef SkillInfo* (__thiscall* LPFN)(void*, int, int);
    return (*(LPFN)0x46CDA0)((void*)0x91AD64, skillId, skillLv);
}
