#include "include/shaiya/include/CObject.h"
using namespace shaiya;

void CObject::PSendViewCombat(CUser* user, void* packet, int _length)
{
    Address u0x4D56D0 = 0x4D56D0;

    __asm
    {
        push _length
        push packet
        mov eax,user
        call u0x4D56D0
    }
}

void CObject::SendView(CObject* object/*ecx*/, void* packet, int _length/*edx*/)
{
    Address u0x4D5250 = 0x4D5250;

    __asm
    {
        mov edx,_length
        mov ecx,object
        push packet
        call u0x4D5250
    }
}
