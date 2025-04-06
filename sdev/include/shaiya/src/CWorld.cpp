#include "include/shaiya/include/CWorld.h"
using namespace shaiya;

CUser* CWorld::FindUser(uint objectId)
{
    typedef CUser* (__stdcall* LPFN)(uint);
    return (*(LPFN)0x414CC0)(objectId);
}

CUser* CWorld::FindUser(const char* charName/*eax*/)
{
    unsigned u0x414CE0 = 0x414CE0;

    __asm
    {
        mov eax,charName
        call u0x414CE0
    }
}

CZone* CWorld::GetZone(int mapId/*eax*/)
{
    unsigned u0x41A250 = 0x41A250;

    __asm
    {
        mov ecx,g_pWorld
        mov eax,mapId
        call u0x41A250
    }
}

void CWorld::SendAll(void* packet/*ecx*/, int _length/*eax*/)
{
    unsigned u0x419120 = 0x419120;

    __asm
    {
        mov esi,g_pWorld
        mov eax,_length
        mov ecx,[packet]
        call u0x419120
    }
}

void CWorld::SendAllCountry(void* packet/*ecx*/, int _length/*eax*/, int country)
{
    unsigned u0x4191B0 = 0x4191B0;

    __asm
    {
        mov esi,g_pWorld
        mov eax,_length
        mov ecx,[packet]
        push country
        call u0x4191B0
    }
}

void CWorld::ZoneLeaveUserMove(CUser* user/*edi*/, int mapId, float x, float y, float z)
{
    unsigned u0x414760 = 0x414760;

    __asm
    {
        sub esp,0xC
        fld [z]
        fstp [esp+0x8]
        fld [y]
        fstp [esp+0x4]
        fld [x]
        fstp [esp]
        push mapId
        mov edi,user
        call u0x414760
    }
}
