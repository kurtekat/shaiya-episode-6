#include "SIMM.h"
using namespace shaiya;

INPUTCONTEXT* SIMM::LockIMC(HIMC himc)
{
    typedef INPUTCONTEXT* (__thiscall* LPFN)(void*, HIMC);
    return (*(LPFN)0x5679B0)((void*)0x22B3F74, himc);
}

int SIMM::UnlockIMC(HIMC himc)
{
    typedef int(__thiscall* LPFN)(void*, HIMC);
    return (*(LPFN)0x5679C0)((void*)0x22B3F74, himc);
}

void* SIMM::LockIMCC(HIMCC himcc)
{
    typedef void* (__thiscall* LPFN)(void*, HIMCC);
    return (*(LPFN)0x5679D0)((void*)0x22B3F74, himcc);
}

int SIMM::UnlockIMCC(HIMCC himcc)
{
    typedef int(__thiscall* LPFN)(void*, HIMCC);
    return (*(LPFN)0x5679E0)((void*)0x22B3F74, himcc);
}
