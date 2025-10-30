#include "CObject.h"
using namespace shaiya;

void CObject::PSendViewCombat(CUser* user, void* packet, int length_)
{
    unsigned u0x4D56D0 = 0x4D56D0;

    __asm
    {
        push length_
        push packet
        mov eax,user
        call u0x4D56D0
    }
}

void CObject::SendView(CObject* object/*ecx*/, void* packet, int length_/*edx*/)
{
    unsigned u0x4D5250 = 0x4D5250;

    __asm
    {
        mov edx,length_
        mov ecx,object
        push packet
        call u0x4D5250
    }
}
