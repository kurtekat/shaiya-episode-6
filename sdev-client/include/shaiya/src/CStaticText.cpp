#include "include/shaiya/include/CStaticText.h"
using namespace shaiya;

CStaticText* CStaticText::Init(const char* text)
{
    typedef CStaticText* (__thiscall* LPFN)(unsigned, const char*);
    return (*(LPFN)0x57C280)(*(unsigned*)0x22B6DD0, text);
}

void CStaticText::Draw(CStaticText* staticText, long x, long y, float extrusion, D3DCOLOR argb)
{
    typedef void(__thiscall* LPFN)(unsigned, CStaticText*, long, long, float, D3DCOLOR);
    (*(LPFN)0x57CA20)(*(unsigned*)0x22B6DD0, staticText, x, y, extrusion, argb);
}

long CStaticText::GetPointX(CStaticText* staticText)
{
    typedef long(__thiscall* LPFN)(unsigned, CStaticText*);
    return (*(LPFN)0x57CC70)(*(unsigned*)0x22B6DD0, staticText);
}
