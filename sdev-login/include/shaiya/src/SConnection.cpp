#include <sdev/include/shaiya/include/SConnection.h>
using namespace shaiya;

void SConnection::Send(SConnection* connection/*ecx*/, void* buf, int len)
{
    typedef void(__thiscall* LPFN)(SConnection*, void*, int);
    (*(LPFN)0x410AE0)(connection, buf, len);
}

void SConnection::Close(SConnection* connection/*ecx*/, int closeType, int closeErr)
{
    typedef void(__thiscall* LPFN)(SConnection*, int, int);
    (*(LPFN)0x410190)(connection, closeType, closeErr);
}
