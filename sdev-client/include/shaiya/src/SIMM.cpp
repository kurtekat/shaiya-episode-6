#include "include/shaiya/include/SIMM.h"
using namespace shaiya;

INPUTCONTEXT* SIMM::LockIMC(HIMC himc)
{
    typedef INPUTCONTEXT* (__thiscall* LPFN)(void*, HIMC);
    return (*(LPFN)0x5679B0)((void*)0x22B3F74, himc);
}

BOOL SIMM::UnlockIMC(HIMC himc)
{
    typedef BOOL(__thiscall* LPFN)(void*, HIMC);
    return (*(LPFN)0x5679C0)((void*)0x22B3F74, himc);
}

void* SIMM::LockIMCC(HIMCC himcc)
{
    typedef void* (__thiscall* LPFN)(void*, HIMCC);
    return (*(LPFN)0x5679D0)((void*)0x22B3F74, himcc);
}

BOOL SIMM::UnlockIMCC(HIMCC himcc)
{
    typedef BOOL(__thiscall* LPFN)(void*, HIMCC);
    return (*(LPFN)0x5679E0)((void*)0x22B3F74, himcc);
}
