#include "include/shaiya/include/CClientToDBAgent.h"
#include "include/shaiya/include/CClientToGameLog.h"
#include "include/shaiya/include/CClientToMgr.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/SConnection.h"
#include "include/shaiya/include/SConnectionTBaseReconnect.h"
#include "include/shaiya/include/network/dbAgent/incoming/0700.h"
#include "include/shaiya/include/network/game/outgoing/1100.h"
#include "include/shaiya/include/network/game/outgoing/F900.h"
using namespace shaiya;

void NetworkHelper::SendMessageToServer(CUser* sender, const char* message)
{
    ChatMessageToServerOutgoing outgoing(sender->charName.data(), message);
    CWorld::SendAll(&outgoing, outgoing.length());
}

void NetworkHelper::SendMessageToServer(const char* senderName, const char* message)
{
    ChatMessageToServerOutgoing outgoing(senderName, message);
    CWorld::SendAll(&outgoing, outgoing.length());
}

void NetworkHelper::SendNotice(const char* message)
{
    AdminCmdNoticeAllOutgoing outgoing(message);
    CWorld::SendAll(&outgoing, outgoing.length());
}

void NetworkHelper::SendNoticeTo(CUser* user, const char* message)
{
    AdminCmdNoticeToOutgoing outgoing(message);
    NetworkHelper::Send(user, &outgoing, outgoing.length());
}

void NetworkHelper::SendNoticeTo(ULONG charId, const char* message)
{
    auto user = CWorld::FindUser(charId);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing outgoing(message);
    NetworkHelper::Send(user, &outgoing, outgoing.length());
}

void NetworkHelper::SendNoticeTo(const char* charName, const char* message)
{
    auto user = CWorld::FindUser(charName);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing outgoing(message);
    NetworkHelper::Send(user, &outgoing, outgoing.length());
}

void NetworkHelper::Send(CUser* user, void* packet, int length)
{
    SConnection::Send(&user->connection.connection, packet, length);
}

void NetworkHelper::SendDBAgent(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToDBAgent->connection, packet, length);
}

void NetworkHelper::SendGameLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToGameLog->connection, packet, length);
}

void NetworkHelper::SendSession(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToMgr->connection, packet, length);
}

void NetworkHelper::SendUserLog(void* packet, int length)
{
    SConnectionTBaseReconnect::Send(&g_pClientToLog->connection, packet, length);
}

void NetworkHelper::SendDBAgentItemCraftName(CUser* user, CItem* item, int bag, int slot)
{
    DBAgentItemCraftNameIncoming craftName(user->userId, bag, slot, item->craftName);
    NetworkHelper::SendDBAgent(&craftName, sizeof(DBAgentItemCraftNameIncoming));
}

void NetworkHelper::SendDBAgentItemGems(CUser* user, CItem* item, int bag, int slot)
{
    DBAgentItemGemsIncoming gems(user->userId, bag, slot, item->gems, user->money);
    NetworkHelper::SendDBAgent(&gems, sizeof(DBAgentItemGemsIncoming));
}
