#include <include/shaiya/include/DBCharacter.h>
using namespace shaiya;

BOOL DBCharacter::ReloadPoint(CUser* user/*esi*/)
{
    Address u0x4235D0 = 0x4235D0;

    __asm
    {
        mov esi,user
        call u0x4235D0
    }
}
