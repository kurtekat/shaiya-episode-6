#include "CWindow.h"
using namespace shaiya;

void CWindow::Draw(LPDIRECT3DBASETEXTURE9 texture, int x, int y)
{
    typedef void(__thiscall* LPFN)(LPDIRECT3DBASETEXTURE9, int, int);
    (*(LPFN)0x57B860)(texture, x, y);
}
