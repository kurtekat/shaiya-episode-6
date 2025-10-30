#include "CStaticText.h"
#include "Static.h"
using namespace shaiya;

SStaticText* CStaticText::Create(const char* text)
{
    typedef SStaticText* (__thiscall* LPFN)(CStaticText*, const char*);
    return (*(LPFN)0x57C280)(g_var->camera.staticText, text);
}

void CStaticText::Draw(SStaticText* staticText, int x, int y, float z, D3DCOLOR color)
{
    typedef void(__thiscall* LPFN)(CStaticText*, SStaticText*, int, int, float, D3DCOLOR);
    (*(LPFN)0x57CA20)(g_var->camera.staticText, staticText, x, y, z, color);
}

int CStaticText::GetTextWidth(const char* text)
{
    typedef int(__thiscall* LPFN)(CStaticText*, const char*);
    return (*(LPFN)0x57CC70)(g_var->camera.staticText, text);
}
