#include "CTexture.h"
using namespace shaiya;

int CTexture::CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, int w, int h)
{
    typedef int(__thiscall* LPFN)(CTexture*, const char*, const char*, int, int);
    return (*(LPFN)0x57B560)(texture, path, fileName, w, h);
}

void CTexture::Render(CTexture* texture, int x, int y, float z)
{
    typedef void(__thiscall* LPFN)(CTexture*, int, int, float);
    (*(LPFN)0x57B680)(texture, x, y, z);
}

void CTexture::Render(CTexture* texture, D3DCOLOR diffuse, 
    int x, int y, float z, 
    int w, int h, 
    float a, float b, float c, float d
)
{
    typedef void(__thiscall* LPFN)(CTexture*, D3DCOLOR, int, int, float, int, int, float, float, float, float);
    (*(LPFN)0x57C000)(texture, diffuse, x, y, z, w, h, a, b, c, d);
}

void CTexture::Reset(CTexture* texture)
{
    typedef void(__thiscall* LPFN)(CTexture*);
    (*(LPFN)0x40FE80)(texture);
}
