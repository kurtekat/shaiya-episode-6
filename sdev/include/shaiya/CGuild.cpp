#include "CGuild.h"
using namespace shaiya;

void CGuild::Send(CGuild* guild, void* packet/*ecx*/, int length_/*eax*/)
{
    unsigned u0x432470 = 0x432470;

    __asm
    {
        push guild
        mov eax,length_
        mov ecx,[packet]
        call u0x432470
    }
}

void CGuild::SendAdmin(CGuild* guild, void* packet/*ecx*/, int length_/*eax*/)
{
    unsigned u0x432C40 = 0x432C40;

    __asm
    {
        push guild
        mov eax,length_
        mov ecx,[packet]
        call u0x432C40
    }
}
