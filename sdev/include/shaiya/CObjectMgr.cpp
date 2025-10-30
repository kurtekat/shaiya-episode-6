#include "CItem.h"
#include "CObjectMgr.h"
using namespace shaiya;

void CObjectMgr::FreeItem(CItem* item/*edi*/)
{
    unsigned u0x411710 = 0x411710;

    __asm
    {
        mov edi,item
        call u0x411710
    }
}
