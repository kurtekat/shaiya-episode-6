#include <include/shaiya/include/CClientToMgr.h>
using namespace shaiya;

void CClientToMgr::OnRecv(void* packet)
{
    typedef void(__thiscall* LPFN)(void*, void*);
    (*(LPFN)0x406960)(nullptr, packet);
}
