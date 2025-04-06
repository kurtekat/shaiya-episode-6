#include "include/shaiya/include/CMap.h"
using namespace shaiya;

CDoor* CMap::GetPortal(CMap* map/*ecx*/, int index/*eax*/)
{
    unsigned u0x430260 = 0x430260;

    __asm
    {
        mov eax,index
        mov ecx,map
        call u0x430260
    }
}

CDoor* CMap::GetPortalById(CMap* map/*ecx*/, int id/*edi*/)
{
    unsigned u0x430230 = 0x430230;

    __asm
    {
        mov edi,id
        mov ecx,map
        call u0x430230
    }
}
