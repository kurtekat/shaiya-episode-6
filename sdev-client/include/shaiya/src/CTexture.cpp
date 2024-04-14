#include <include/shaiya/include/CTexture.h>
using namespace shaiya;

void CTexture::Draw(CTexture* texture, long x, long y, float extrusion)
{
    typedef void(__thiscall* LPFN)(CTexture*, long, long, float);
    (*(LPFN)0x57B680)(texture, x, y, extrusion);
}

void CTexture::Draw(CTexture* texture, float top, float left, float right, float bottom)
{
    typedef void(__thiscall* LPFN)(CTexture*, float, float, float, float);
    (*(LPFN)0x57BEC0)(texture, top, left, right, bottom);
}
