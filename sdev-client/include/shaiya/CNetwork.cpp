#include "CNetwork.h"
using namespace shaiya;

void CNetwork::Send(void* buf, int len)
{
    typedef void(__cdecl* LPFN)(void*, int);
    (*(LPFN)0x5EA9A0)(buf, len);
}
