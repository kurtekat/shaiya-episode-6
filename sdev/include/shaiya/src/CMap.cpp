#include <include/shaiya/include/CMap.h>
using namespace shaiya;

CDoor* CMap::GetPortal(CMap* map/*ecx*/, int index/*eax*/)
{
    Address u0x430260 = 0x430260;

    __asm
    {
        mov eax,index
        mov ecx,map
        call u0x430260
    }
}

CDoor* CMap::GetPortalById(CMap* map/*ecx*/, int insZoneId/*edi*/)
{
    Address u0x430230 = 0x430230;

    __asm
    {
        mov edi,insZoneId
        mov ecx,map
        call u0x430230
    }
}

bool CMap::IsStatic(CMap* map/*ecx*/)
{
    typedef bool(__thiscall* LPFN)(CMap*);
    return (*(LPFN)0x4033D0)(map);
}
