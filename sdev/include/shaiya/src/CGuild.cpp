#include "include/shaiya/include/CGuild.h"
using namespace shaiya;

void CGuild::Send(CGuild* guild, void* packet/*ecx*/, int _length/*eax*/)
{
    Address u0x432470 = 0x432470;

    __asm
    {
        push guild
        mov eax,_length
        mov ecx,[packet]
        call u0x432470
    }
}

void CGuild::SendAdmin(CGuild* guild, void* packet/*ecx*/, int _length/*eax*/)
{
    Address u0x432C40 = 0x432C40;

    __asm
    {
        push guild
        mov eax,_length
        mov ecx,[packet]
        call u0x432C40
    }
}
