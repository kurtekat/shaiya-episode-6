#include <include/shaiya/include/CDataFile.h>
using namespace shaiya;

CDataFile::ItemInfo* CDataFile::GetItemInfo(int type, int typeId)
{
    typedef ItemInfo* (__thiscall* LPFN)(void*, int, int);
    return (*(LPFN)0x46CB30)((void*)0x91AD64, type, typeId);
}

CDataFile::MobInfo* CDataFile::GetMobInfo(int mobId)
{
    typedef MobInfo* (__thiscall* LPFN)(void*, int);
    return (*(LPFN)0x46CCA0)((void*)0x91AD64, mobId);
}

CDataFile::SkillInfo* CDataFile::GetSkillInfo(int skillId, int skillLv)
{
    typedef SkillInfo* (__thiscall* LPFN)(void*, int, int);
    return (*(LPFN)0x46CDA0)((void*)0x91AD64, skillId, skillLv);
}
