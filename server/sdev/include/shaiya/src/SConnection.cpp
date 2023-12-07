#include <include/shaiya/include/SConnection.h>
using namespace shaiya;

void SConnection::Send(SConnection* connection/*ecx*/, void* buf, int len)
{
    typedef void(__thiscall* LPFN)(SConnection*, void*, int);
    (*(LPFN)0x4ED0E0)(connection, buf, len);
}

void SConnection::Close(SConnection* connection/*ecx*/, int closeType, int closeErr)
{
    typedef void(__thiscall* LPFN)(SConnection*, int, int);
    (*(LPFN)0x4EC760)(connection, closeType, closeErr);
}

bool SConnection::IsConnected(SConnection* connection/*ecx*/)
{
    typedef bool(__thiscall* LPFN)(SConnection*);
    return (*(LPFN)0x405920)(connection);
}
