#include "SConnection.h"
using namespace shaiya;

void SConnection::Send(SConnection* connection/*ecx*/, void* buffer, int length)
{
    typedef void(__thiscall* LPFN)(SConnection*, void*, int);
    (*(LPFN)0x410AE0)(connection, buffer, length);
}

void SConnection::Close(SConnection* connection/*ecx*/, int closeType, int closeError)
{
    typedef void(__thiscall* LPFN)(SConnection*, int, int);
    (*(LPFN)0x410190)(connection, closeType, closeError);
}
