#include "include/static.h"
using namespace shaiya;

void Static::DrawRect(D3DCOLOR argb, int x, int y, int w, int h)
{
    typedef void(__cdecl* LPFN)(D3DCOLOR, int, int, int, int);
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

void Static::SysMsgToChatBox(int messageType, int messageNumber, int unknown)
{
    typedef void(__cdecl* LPFN)(int, int, int);
    (*(LPFN)0x423150)(messageType, messageNumber, unknown);
}
