#include <shaiya/include/common/PartyType.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CParty.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/network/game/incoming/0B00.h"
#include "include/shaiya/include/network/game/outgoing/0B00.h"
using namespace shaiya;

namespace packet_party
{
    /// <summary>
    /// Handles incoming 0xB1C packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void map_ping_handler(CUser* user, PartyMapPingIncoming* incoming)
    {
        if (user->status == CUser::Status::Death)
            return;

        if (!user->party)
            return;

        switch (incoming->partyType)
        {
        case UnionType::Leader:
        {
            if (!CParty::IsPartyBoss(user->party, user))
                return;
            break;
        }
        case UnionType::SubLeader:
        {
            if (!CParty::IsPartySubBoss(user->party, user))
                return;
            break;
        }
        default:
            return;
        }

        PartyMapPingOutgoing outgoing(incoming->x, incoming->y, incoming->partyType);
        CParty::Send(user->party, &outgoing, sizeof(PartyMapPingOutgoing));
    }
}

unsigned u0x4752F0 = 0x4752F0;
unsigned u0x475FE1 = 0x475FE1;
void __declspec(naked) naked_0x4752EB()
{
    __asm
    {
        // original
        add eax,-0xB02
        cmp eax,0x1A
        je case_0xB1C
        jmp u0x4752F0

        case_0xB1C:
        pushad

        push ebx // packet
        push ebp // user
        call packet_party::map_ping_handler
        add esp,0x8

        popad

        jmp u0x475FE1
    }
}

void hook::packet_party()
{
    // CUser::PacketParty (switch)
    util::detour((void*)0x4752EB, naked_0x4752EB, 5);
}
