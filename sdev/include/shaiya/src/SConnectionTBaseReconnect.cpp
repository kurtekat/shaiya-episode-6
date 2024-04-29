#include <include/shaiya/include/SConnectionTBaseReconnect.h>
using namespace shaiya;

void SConnectionTBaseReconnect::Send(SConnection* connection, void* buf, int len)
{
    typedef void(__thiscall* LPFN)(void*, void*, int);
    (*(LPFN)0x4ED2D0)(connection, buf, len);
}
