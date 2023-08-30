#include <include/shaiya/include/CGuild.h>
using namespace shaiya;

void CGuild::Send(CGuild* guild, void* data/*ecx*/, int len/*eax*/)
{
    Address u0x432470 = 0x432470;

    __asm
    {
        push guild
        mov eax,len
        mov ecx,[data]
        call u0x432470
    }
}

void CGuild::SendAdmin(CGuild* guild, void* data/*ecx*/, int len/*eax*/)
{
    Address u0x432C40 = 0x432C40;

    __asm
    {
        push guild
        mov eax,len
        mov ecx,[data]
        call u0x432C40
    }
}
