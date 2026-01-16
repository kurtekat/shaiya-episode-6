#include <algorithm>
#include <util/util.h>
#include <shaiya/include/network/TP_MAIN.h>
#include <shaiya/include/network/game/incoming/0200.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include "include/main.h"
#include "include/shaiya/BattlefieldMoveInfo.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/RevengeMark.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

namespace packet_main_interface
{
    void handler_0x245(CUser* user, GameMovePvPZoneIncoming* incoming)
    {
        if (user->status == UserStatus::Death)
            return;

        if (user->mapId == incoming->mapId)
            return;

        auto it = g_pvpZones.find(incoming->mapId);
        if (it == g_pvpZones.end())
            return;

        auto& info = it->second;
        if (user->level < info.levelMin || user->level > info.levelMax)
            return;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);

        auto index = std::clamp(static_cast<int>(user->family), 0, 3);
        auto mapId = info.mapPos[index].mapId;
        auto x = info.mapPos[index].x;
        auto y = info.mapPos[index].y;
        auto z = info.mapPos[index].z;
        UserHelper::SetMovePosition(user, mapId, x, y, z, UserMovePosType::MovePvPZone, 0);
    }

    void send_0x229(CUser* target, CUser* killer)
    {
        if (auto outer = g_revengeMarks.find(killer->id); outer != g_revengeMarks.end())
        {
            if (auto inner = outer->second.find(target->id); inner != outer->second.end())
            {
                outer->second.erase(inner);
                RevengeMark::send(killer, target->id, 0);
            }
        }

        if (auto outer = g_revengeMarks.find(target->id); outer != g_revengeMarks.end())
        {
            if (auto inner = outer->second.find(killer->id); inner != outer->second.end())
            {
                if (inner->second < 999)
                {
                    ++inner->second;
                    RevengeMark::send(target, inner->first, inner->second);
                }
            }
            else
            {
                outer->second.insert({ killer->id, 1 });
                RevengeMark::send(target, killer->id, 1);
            }
        }
        else
        {
            g_revengeMarks.insert({ target->id, {{ killer->id, 1 }} });
            RevengeMark::send(target, killer->id, 1);
        }
    }

    void handler(CUser* user, TP_MAIN* packet)
    {
        switch (packet->opcode)
        {
        case 0x245:
            handler_0x245(user, reinterpret_cast<GameMovePvPZoneIncoming*>(packet));
            break;
        default:
            SConnection::Close(user, 9, 0);
            break;
        }
    }
}

unsigned u0x477999 = 0x477999;
void __declspec(naked) naked_0x47798E()
{
    __asm
    {
        pushad

        push ebx // packet
        push ebp // user
        call packet_main_interface::handler
        add esp,0x8

        popad

        jmp u0x477999
    }
}

unsigned u0x4656FD = 0x4656FD;
void __declspec(naked) naked_0x4656F7()
{
    __asm
    {
        pushad

        push esi // killer
        push edi // target
        call packet_main_interface::send_0x229
        add esp,0x8

        popad

        // original
        mov ebx,[esi+0x17F4]
        jmp u0x4656FD
    }
}

void hook::packet_main_interface()
{
    // CUser::PacketMainInterface (default case)
    util::detour((void*)0x47798E, naked_0x47798E, 6);
    // CUser::Death
    util::detour((void*)0x4656F7, naked_0x4656F7, 6);
}
