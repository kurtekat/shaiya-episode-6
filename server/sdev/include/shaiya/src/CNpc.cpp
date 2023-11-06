#include <include/shaiya/include/CNpc.h>
#include <include/shaiya/include/CUser.h>
using namespace shaiya;

void CNpc::SetStatus(CNpc* npc/*eax*/, int status/*ecx*/)
{
    Address u0x4D45F0 = 0x4D45F0;

    __asm
    {
        mov ecx,status
        mov eax,npc
        call u0x4D45F0
    }
}

void CNpc::SetTarget(CNpc* npc/*eax*/, CUser* user/*esi*/)
{
    Address u0x4D4550 = 0x4D4550;

    __asm
    {
        mov esi,user
        mov eax,npc
        call u0x4D4550
    }
}

void CNpc::StatusChange(CNpc* npc/*eax*/, int nextStatus/*ecx*/)
{
    Address u0x4D4600 = 0x4D4600;

    __asm
    {
        mov ecx,nextStatus
        mov eax,npc
        call u0x4D4600
    }
}

void CNpc::StatusAttackStop(CNpc* npc/*eax*/)
{
    Address u0x4D4610 = 0x4D4610;

    __asm
    {
        mov eax,npc
        call u0x4D4610
    }
}
