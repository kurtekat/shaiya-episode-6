#include "CClientToDBAgent.h"
#include "CClientToGameLog.h"
#include "CClientToMgr.h"
#include "CLogConnection.h"
#include "CUser.h"
#include "NetworkHelper.h"
#include "SConnection.h"
#include "SConnectionTBaseReconnect.h"
using namespace shaiya;

void NetworkHelper::Send(CUser* user, void* packet, int length)
{
    SConnection::Send(user, packet, length);
}

void NetworkHelper::SendDBAgent(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToDBAgent, packet, length);
}

void NetworkHelper::SendGameLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToGameLog, packet, length);
}

void NetworkHelper::SendSession(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToMgr, packet, length);
}

void NetworkHelper::SendUserLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(g_pClientToLog, packet, length);
}
