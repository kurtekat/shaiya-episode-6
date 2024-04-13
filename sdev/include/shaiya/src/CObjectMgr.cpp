#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CObjectMgr.h>
using namespace shaiya;

void CObjectMgr::FreeItem(CItem* item/*edi*/)
{
    Address u0x411710 = 0x411710;

    __asm
    {
        mov edi,item
        call u0x411710
    }
}
