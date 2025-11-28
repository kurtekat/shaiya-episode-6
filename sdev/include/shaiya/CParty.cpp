#include "CParty.h"
using namespace shaiya;

CUser* CParty::FindUser(CParty* party/*edi*/, unsigned objectId)
{
    unsigned u0x44E8B0 = 0x44E8B0;

    __asm
    {
        push objectId
        mov edi,party
        call u0x44E8B0
    }
}

bool CParty::IsPartyBoss(CParty* party/*esi*/, CUser* user)
{
    unsigned u0x44E260 = 0x44E260;

    __asm
    {
        push user
        mov esi,party
        call u0x44E260
    }
}

bool CParty::IsPartySubBoss(CParty* party/*esi*/, CUser* user)
{
    unsigned u0x44E2A0 = 0x44E2A0;

    __asm
    {
        push user
        mov esi,party
        call u0x44E2A0
    }
}

int CParty::GetGroup(CParty* party/*eax*/, CUser* user)
{
    unsigned u0x44ECF0 = 0x44ECF0;

    __asm
    {
        push user
        mov eax,party
        call u0x44ECF0
    }
}

CUser* CParty::GetPartyBoss(CParty* party/*esi*/)
{
    unsigned u0x44E2F0 = 0x44E2F0;

    __asm
    {
        mov esi,party
        call u0x44E2F0
    }
}

CUser* CParty::GetPartySubBoss(CParty* party/*esi*/)
{
    unsigned u0x44E320 = 0x44E320;

    __asm
    {
        mov esi,party
        call u0x44E320
    }
}

void CParty::LeaveParty(CUser* user/*eax*/, CParty* party/*ecx*/)
{
    unsigned u0x44F5F0 = 0x44F5F0;

    __asm
    {
        mov eax,user
        mov ecx,party
        call u0x44F5F0
    }
}

void CParty::Send(CParty* party/*esi*/, void* packet/*ecx*/, int length_/*eax*/)
{
    unsigned u0x44E950 = 0x44E950;

    __asm
    {
        mov esi,party
        mov eax,length_
        mov ecx,[packet]
        call u0x44E950
    }
}
