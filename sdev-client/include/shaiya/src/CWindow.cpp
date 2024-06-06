#include "include/shaiya/include/CWindow.h"
using namespace shaiya;

void CWindow::Draw(LPDIRECT3DBASETEXTURE9 texture, long x, long y)
{
    typedef void(__thiscall* LPFN)(LPDIRECT3DBASETEXTURE9, long, long);
    (*(LPFN)0x57B860)(texture, x, y);
}
