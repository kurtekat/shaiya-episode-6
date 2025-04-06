#include "include/shaiya/include/CTexture.h"
using namespace shaiya;

int CTexture::CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, long w, long h)
{
    typedef int(__thiscall* LPFN)(CTexture*, const char*, const char*, long, long);
    return (*(LPFN)0x57B560)(texture, path, fileName, w, h);
}

void CTexture::Render(CTexture* texture, long x, long y, float z)
{
    typedef void(__thiscall* LPFN)(CTexture*, long, long, float);
    (*(LPFN)0x57B680)(texture, x, y, z);
}

void CTexture::Render(CTexture* texture, D3DCOLOR diffuse, 
    long x, long y, float z, 
    long w, long h, 
    float a, float b, float c, float d
)
{
    typedef void(__thiscall* LPFN)(CTexture*, D3DCOLOR, long, long, float, long, long, float, float, float, float);
    (*(LPFN)0x57C000)(texture, diffuse, x, y, z, w, h, a, b, c, d);
}
