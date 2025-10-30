#include "CEffectData.h"
using namespace shaiya;

int CEffectData::CreateFromFile(CEffectData* effectData, const char* path, const char* fileName/*.eft*/)
{
    typedef int(__thiscall* LPFN)(CEffectData*, const char*, const char*);
    return (*(LPFN)0x58C460)(effectData, path, fileName);
}
