#include "include/static.h"
using namespace shaiya;

void Static::DrawRect(D3DCOLOR argb, long x, long y, long w, long h)
{
    typedef void(__cdecl* LPFN)(D3DCOLOR, long, long, long, long);
    (*(LPFN)0x4B6180)(argb, x, y, w, h);
}

int Static::GetDaSkillEffectDataId(int skillId)
{
    typedef int(__cdecl* LPFN)(int);
    return (*(LPFN)0x5AB4E0)(skillId);
}

char* Static::GetMsg(int messageNumber)
{
    typedef char* (__cdecl* LPFN)(int);
    return (*(LPFN)0x420DB0)(messageNumber);
}

bool Static::PlayWav(const char* wavFileName, D3DVECTOR* origin, float volume, bool repeat)
{
    typedef bool(__thiscall* LPFN)(void*, const char*, D3DVECTOR*, float, bool);
    return (*(LPFN)0x56C650)((void*)0x22B4030, wavFileName, origin, volume, repeat);
}

void Static::MsgTextOut(int messageType, int messageNumber, int unknown)
{
    typedef void(__cdecl* LPFN)(int, int, int);
    (*(LPFN)0x423150)(messageType, messageNumber, unknown);
}
