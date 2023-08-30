#include <include/shaiya/include/CWorld.h>
using namespace shaiya;

CUser* CWorld::FindUser(ULONG id/*CUser->id*/)
{
    typedef CUser* (__stdcall* LPFN)(ULONG);
    return (*(LPFN)0x414CC0)(id);
}

CUser* CWorld::FindUser(const char* charName/*eax*/)
{
    Address u0x414CE0 = 0x414CE0;

    __asm
    {
        mov eax,charName
        call u0x414CE0
    }
}

int CWorld::GetUserCount()
{
    typedef int(__stdcall* LPFN)();
    return (*(LPFN)0x408C60)();
}

CZone* CWorld::GetZone(int mapId/*eax*/)
{
    Address u0x41A250 = 0x41A250;

    __asm
    {
        mov ecx,g_pWorld
        mov eax,mapId
        call u0x41A250
    }
}

ULONG CWorld::GetWorldDay()
{
    typedef ULONG(__stdcall* LPFN)();
    return (*(LPFN)0x47A670)();
}

void CWorld::SendAll(void* data/*ecx*/, int len/*eax*/)
{
    Address u0x419120 = 0x419120;

    __asm
    {
        mov esi,g_pWorld
        mov eax,len
        mov ecx,[data]
        call u0x419120
    }
}

void CWorld::SendAllCountry(void* data/*ecx*/, int len/*eax*/, int country)
{
    Address u0x4191B0 = 0x4191B0;

    __asm
    {
        mov esi,g_pWorld
        mov eax,len
        mov ecx,[data]
        call u0x4191B0
    }
}

void CWorld::SetWorldDay(ULONG time/*eax*/)
{
    Address u0x405A10 = 0x405A10;

    __asm
    {
        mov eax,time
        call u0x405A10
    }
}
