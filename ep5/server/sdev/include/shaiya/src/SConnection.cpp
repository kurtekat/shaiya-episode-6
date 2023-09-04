#include <shaiya/include/SConnection.h>
using namespace shaiya;

void SConnection::Send(CUser* user/*ecx*/, void* buf, int len)
{
    typedef void(__thiscall* LPFN)(CUser*, void*, int);
    (*(LPFN)0x4ED0E0)(user, buf, len);
}

void SConnection::Close(CUser* user/*ecx*/, int closeType, int closeErr)
{
    typedef void(__thiscall* LPFN)(CUser*, int, int);
    (*(LPFN)0x4EC760)(user, closeType, closeErr);
}
