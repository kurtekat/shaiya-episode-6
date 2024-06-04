#include <include/shaiya/include/ItemEnchant.h>
using namespace shaiya;

UINT32 shaiya::GetGemMoneyByGrade(int grade)
{
    Address u0x46C720 = 0x46C720;

    __asm
    {
        mov eax,grade
        call u0x46C720
    }
}
