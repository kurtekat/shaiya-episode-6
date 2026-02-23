#include "CMessage.h"
using namespace shaiya;

CMessage* CMessage::Init(void* block, int buttonsFlag, int textR, int textG, int textB, const char* text, int bgImageFlag)
{
    typedef CMessage* (__thiscall* LPFN)(void*, int, int, int, int, const char*, int);
    return (*(LPFN)0x4DC9A0)(block, buttonsFlag, textR, textG, textB, text, bgImageFlag);
}

int CMessage::DialogResult(CMessage* message)
{
    typedef int(__thiscall* LPFN)(CMessage*);
    return (*(LPFN)0x4DC5C0)(message);
}

void CMessage::Show(CMessage* message)
{
    typedef void(__thiscall* LPFN)(CMessage*);
    (*(LPFN)0x4DC770)(message);
}

void CMessage::Hide(CMessage* message)
{
    typedef void(__thiscall* LPFN)(CMessage*);
    (*(LPFN)0x4DD380)(message);
}
