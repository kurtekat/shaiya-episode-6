#include "SConnectionTBaseReconnect.h"
using namespace shaiya;

void SConnectionTBaseReconnect::Send(SConnection* connection, void* packet, int length)
{
    typedef void(__thiscall* LPFN)(void*, void*, int);
    (*(LPFN)0x4ED2D0)(connection, packet, length);
}
