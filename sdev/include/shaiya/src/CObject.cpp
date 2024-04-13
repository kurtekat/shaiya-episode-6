#include <include/shaiya/include/CObject.h>
using namespace shaiya;

void CObject::PSendViewCombat(CUser* user, void* data, int len)
{
    Address u0x4D56D0 = 0x4D56D0;

    __asm
    {
        push len
        push data
        mov eax,user
        call u0x4D56D0
    }
}
