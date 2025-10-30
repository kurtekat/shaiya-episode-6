#include "Static.h"
using namespace shaiya;

void Static::DrawRect(D3DCOLOR argb, int x, int y, int w, int h)
{
    typedef void(__cdecl* LPFN)(D3DCOLOR, int, int, int, int);
    (*(LPFN)0x4B6180)(argb, x, y, w, h);
}

void Static::DrawText_ChatBox(ChatType chatType, const char* text, int unknown)
{
    typedef void(__cdecl* LPFN)(ChatType, const char*, int);
    (*(LPFN)0x4231A0)(chatType, text, unknown);
}

void Static::DrawText_ViewPoint(int x, int y, D3DCOLOR color, const char* text)
{
    typedef void(__cdecl* LPFN)(int, int, D3DCOLOR, const char*);
    (*(LPFN)0x531640)(x, y, color, text);
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

void Static::SysMsgToChatBox(ChatType chatType, int messageNumber, int unknown)
{
    typedef void(__cdecl* LPFN)(ChatType, int, int);
    (*(LPFN)0x423150)(chatType, messageNumber, unknown);
}
