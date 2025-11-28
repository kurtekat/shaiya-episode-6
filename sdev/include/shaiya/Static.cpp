#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Static.h"
using namespace shaiya;

void Static::ConvTime(time32_t time/*eax*/, SYSTEMTIME* output/*ecx*/)
{
    unsigned u0x4E1CA0 = 0x4E1CA0;

    __asm
    {
        mov eax,output
        mov ecx,time
        call u0x4E1CA0
    }
}

time32_t Static::ConvTime(SYSTEMTIME* time/*ecx*/)
{
    unsigned u0x4E1CF0 = 0x4E1CF0;

    __asm
    {
        mov ecx,time
        call u0x4E1CF0
    }
}

time32_t Static::GetSystemTime()
{
    typedef time32_t(__stdcall* LPFN)();
    return (*(LPFN)0x4E1A50)();
}
