#include "CClientToDBAgent.h"
#include "CClientToGameLog.h"
#include "CClientToMgr.h"
#include "CLogConnection.h"
#include "Network.h"
#include "SConnectionTBaseReconnect.h"
using namespace shaiya;

void Network::SendDBAgent(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToDBAgent, packet, length);
}

void Network::SendGameLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToGameLog, packet, length);
}

void Network::SendSession(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToMgr, packet, length);
}

void Network::SendUserLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToLog, packet, length);
}
