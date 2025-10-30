#include "SConnection.h"
using namespace shaiya;

void SConnection::Send(SConnection* connection/*ecx*/, void* packet, int length)
{
    typedef void(__thiscall* LPFN)(SConnection*, void*, int);
    (*(LPFN)0x4ED0E0)(connection, packet, length);
}

void SConnection::Close(SConnection* connection/*ecx*/, int closeType, int closeError)
{
    typedef void(__thiscall* LPFN)(SConnection*, int, int);
    (*(LPFN)0x4EC760)(connection, closeType, closeError);
}
