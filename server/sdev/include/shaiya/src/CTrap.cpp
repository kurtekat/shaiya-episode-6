#include <include/shaiya/include/CTrap.h>
using namespace shaiya;

void CTrap::GetCountry(CTrap* trap/*eax*/)
{
    Address u0x4280F0 = 0x4280F0;

    __asm
    {
        mov eax,trap
        call u0x4280F0
    }
}

void CTrap::SetCountry(CTrap* trap/*eax*/, int country)
{
    Address u0x45DE80 = 0x45DE80;

    __asm
    {
        push country
        mov eax,trap
        call u0x45DE80
    }
}
