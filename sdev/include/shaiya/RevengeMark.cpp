#include <shaiya/include/network/game/outgoing/0200.h>
#include "CUser.h"
#include "RevengeMark.h"
#include "SConnection.h"
using namespace shaiya;

void RevengeMark::SendKillCount(CUser* user, unsigned killerId, unsigned killCount)
{
    GameRevengeMarkOutgoing outgoing{};
    outgoing.charId = killerId;
    outgoing.killCount = killCount;
    SConnection::Send(user, &outgoing, sizeof(GameRevengeMarkOutgoing));
}

void RevengeMark::SendRevengeSuccess(CUser* user, unsigned targetId)
{
    GameRevengeMarkOutgoing outgoing{};
    outgoing.charId = targetId;
    outgoing.killCount = 0;
    SConnection::Send(user, &outgoing, sizeof(GameRevengeMarkOutgoing));
}
