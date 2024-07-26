#include "include/static.h"
using namespace shaiya;

void Static::DrawSystemMessage(int type, int lineNumber, int unknown)
{
    typedef void(__cdecl* LPFN)(int, int, int);
    (*(LPFN)0x423150)(type, lineNumber, unknown);
}

int Static::GetDaSkillEffectDataId(int skillId)
{
    typedef int(__cdecl* LPFN)(int);
    return (*(LPFN)0x5AB4E0)(skillId);
}

bool Static::PlayWav(const char* filename, D3DVECTOR* origin, float volume, bool repeat)
{
    typedef bool(__thiscall* LPFN)(void*, const char*, D3DVECTOR*, float, bool);
    return (*(LPFN)0x56C650)((void*)0x22B4030, filename, origin, volume, repeat);
}