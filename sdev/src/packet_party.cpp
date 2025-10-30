#include <util/util.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/network/game/incoming/0B00.h>
#include <shaiya/include/network/game/outgoing/0B00.h>
#include "include/main.h"
#include "include/shaiya/CParty.h"
#include "include/shaiya/CUser.h"
using namespace shaiya;

namespace packet_party
{
    /// <summary>
    /// Handles incoming 0xB1C packets.
    /// </summary>
    void handler_0xB1C(CUser* user, GamePartyBossMapPosIncoming* incoming)
    {
        if (user->status == UserStatus::Death)
            return;

        if (!user->party)
            return;

        switch (incoming->partyType)
        {
        case UnionType::Boss:
        {
            if (!CParty::IsPartyBoss(user->party, user))
                return;
            break;
        }
        case UnionType::SubBoss:
        {
            if (!CParty::IsPartySubBoss(user->party, user))
                return;
            break;
        }
        default:
            return;
        }

        GamePartyBossMapPosOutgoing outgoing{};
        outgoing.x = incoming->x;
        outgoing.y = incoming->y;
        outgoing.partyType = incoming->partyType;
        CParty::Send(user->party, &outgoing, sizeof(GamePartyBossMapPosOutgoing));
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
        call packet_party::handler_0xB1C
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
