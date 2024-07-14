#include "include/shaiya/include/CTexture.h"
using namespace shaiya;

BOOL CTexture::CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, long w, long h)
{
    typedef BOOL(__thiscall* LPFN)(CTexture*, const char*, const char*, long, long);
    return (*(LPFN)0x57B560)(texture, path, fileName, w, h);
}

void CTexture::Draw(CTexture* texture, long x, long y, float extrusion)
{
    typedef void(__thiscall* LPFN)(CTexture*, long, long, float);
    (*(LPFN)0x57B680)(texture, x, y, extrusion);
}
