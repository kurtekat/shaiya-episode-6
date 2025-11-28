#include <shaiya/include/network/game/outgoing/0200.h>
#include "CUser.h"
#include "NetworkHelper.h"
#include "RevengeMark.h"
using namespace shaiya;

void RevengeMark::send(CUser* user, unsigned charId, unsigned killCount)
{
    GameRevengeMarkOutgoing outgoing{};
    outgoing.charId = charId;
    outgoing.killCount = killCount;
    NetworkHelper::Send(user, &outgoing, sizeof(GameRevengeMarkOutgoing));
}
