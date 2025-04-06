#include "include/shaiya/include/CClientToDBAgent.h"
#include "include/shaiya/include/CClientToGameLog.h"
#include "include/shaiya/include/CClientToMgr.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/SConnection.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
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
