#include "include/shaiya/include/CParty.h"
using namespace shaiya;

CUser* CParty::FindUser(CParty* party/*edi*/, ULONG id/*CUser->id*/)
{
    Address u0x44E8B0 = 0x44E8B0;

    __asm
    {
        push id
        mov edi,party
        call u0x44E8B0
    }
}

void CParty::LeaveParty(CUser* user/*eax*/, CParty* party/*ecx*/)
{
    Address u0x44F5F0 = 0x44F5F0;

    __asm
    {
        mov eax,user
        mov ecx,party
        call u0x44F5F0
    }
}

void CParty::Send(CParty* party/*esi*/, void* data/*ecx*/, int len/*eax*/)
{
    Address u0x44E950 = 0x44E950;

    __asm
    {
        mov esi,party
        mov eax,len
        mov ecx,[data]
        call u0x44E950
    }
}
