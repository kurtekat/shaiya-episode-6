#include <shaiya/include/network/game/outgoing/0200.h>
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/RevengeMark.h"
using namespace shaiya;

void RevengeMark::send(CUser* user, uint charId, uint killCount)
{
    GameRevengeMarkOutgoing outgoing{};
    outgoing.charId = charId;
    outgoing.killCount = killCount;
    NetworkHelper::Send(user, &outgoing, sizeof(GameRevengeMarkOutgoing));
}
