#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Static.h"
using namespace shaiya;

void Static::ConvTime(uint_t time/*eax*/, SYSTEMTIME* output/*ecx*/)
{
    unsigned u0x4E1CA0 = 0x4E1CA0;

    __asm
    {
        mov eax,output
        mov ecx,time
        call u0x4E1CA0
    }
}

uint_t Static::ConvTime(SYSTEMTIME* time/*ecx*/)
{
    unsigned u0x4E1CF0 = 0x4E1CF0;

    __asm
    {
        mov ecx,time
        call u0x4E1CF0
    }
}

uint_t Static::GetSystemTime()
{
    typedef uint_t(__stdcall* LPFN)();
    return (*(LPFN)0x4E1A50)();
}
